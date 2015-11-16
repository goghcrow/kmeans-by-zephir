namespace KMeans;

// use \SplObjectStorage;
// use \LogicException;
// use \InvalidArgumentException;

class Space extends \SplObjectStorage
{
	// Default seeding method, initial cluster centroid are randomly choosen
	const SEED_DEFAULT  = 1;

	// Alternative seeding method by David Arthur and Sergei Vassilvitskii
	// (see http://en.wikipedia.org/wiki/K-means++)
	const SEED_DASV = 2;


	protected dimention  = 0 { get };

	public function __construct(int dimention = 2)
	{
		if unlikely dimention < 1 {
			throw new \LogicException("a space dimention cannot be null or negative");
		}

		let this->dimention = dimention;
	}

	public function toArray() -> array
	{
		var point = null;
		array points = [];

		for point in iterator(this) {
			let points[] = (array)<\KMeans\Point>point->toArray();
		}

		return ["points" : points];
	}

	public function newPoint(array coordinates) -> <\KMeans\Point>
	{
		if unlikely count(coordinates) !== this->dimention {
			throw new \LogicException("(" . implode(",", coordinates) . ") is not a point of this space");
		}

		return new Point(this, coordinates);
	}

	public function addPoint(array coordinates, data = null) -> void
	{
		this->attach(this->newPoint(coordinates), data);
	}

	public function attach(<\KMeans\Point> point, data = null) -> void
	{
		if point instanceof Point {
			parent::attach(point, data);
		} else {
			throw new \InvalidArgumentException("can only attach points to spaces");
		}
	}

	public function getBoundaries() -> array
	{
		int n = 0;
		var min = null,
			max = null,
			point = null;

		if this->count() === 0 {
			return [];
		}

		let min = this->newPoint(array_fill(0, this->dimention, null));
		let max = this->newPoint(array_fill(0, this->dimention, null));

		for point in iterator(this) {
			for n in range(0, this->dimention - 1) {
				if (min->offsetGet(n) > point->offsetGet(n)) || (min->offsetGet(n) === null) {
					min->offsetSet(n, point->offsetGet(n));
				} elseif (max->offsetGet(n) < point->offsetGet(n)) || (max->offsetGet(n) === null) {
					max->offsetSet(n, point->offsetGet(n));
				}
			}
		}

		return [min, max];
	}

	public function getRandomPoint(<\KMeans\Point> min, <\KMeans\Point> max) -> <\KMeans\Point>
	{
		int n = 0;
		var point = this->newPoint((array)array_fill(0, this->dimention, null));

		for n in range(0, this->dimention - 1) {
			point->offsetSet(n, (double)rand(<\SplObjectStorage> min->offsetGet(n), <\SplObjectStorage> max->offsetGet(n)));
		}

		return point;
	}

	public function solve(int nbClusters, int seed = self::SEED_DEFAULT, var iterationCallback = null) -> array|<\KMeans\Cluster>
	{
		array clusters = [];

		if (iterationCallback && !is_callable(iterationCallback)) {
			throw new \InvalidArgumentException("invalid iteration callback");
		}

		// initialize K clusters
		let clusters = (array)this->initializeClusters(nbClusters, seed);

		// there's only one cluster, clusterization has no meaning
		if (count(clusters) === 1) {
			return clusters[0];
		}

		// until convergence is reached
		do {
			if unlikely iterationCallback {
				{iterationCallback}(this, clusters);
			}
		} while (this->iterate(clusters));

		// clustering is done.
		return clusters;
	}

	protected function initializeClusters(int nbClusters, int seed) -> array
	{
		var min = null,
			max = null,
			distances = null,
			point = null;
		int n = 0,
			i = 0,
			position = 0;
		double sum = 0.0, distance = 0.0;
		array clusters = [];

		if (nbClusters <= 0) {
			throw new \InvalidArgumentException("invalid clusters number");
		}

		switch (seed) {
			// the default seeding method chooses completely random centroid
			case self::SEED_DEFAULT:
				// get the space boundaries to avoid placing clusters centroid too far from points
				// list($min, $max) = $this->getBoundaries();
				array boundaries = (array)this->getBoundaries();
				if empty boundaries {
					// FIXME
				} else {
					let min = boundaries[0];
					let max = boundaries[1];
				}

				// initialize N clusters with a random point within space boundaries
				for n in range(0, nbClusters - 1) {
					let clusters[] = new Cluster(this, this->getRandomPoint(min, max)->getCoordinates());
				}
				break;

			// the DASV seeding method consists of finding good initial centroids for the clusters
			case self::SEED_DASV:
				// find a random point
				let position = (int)rand(1, this->count());
				let i = 1;
				this->rewind();
				while (i < position) && this->valid() {
					let i++;
					this->next();
				}
				let clusters[] = new Cluster(this, this->current()->getCoordinates());

				// retains the distances between points and their closest clusters
				let distances = new \SplObjectStorage;

				// create k clusters
				for i in range(1, nbClusters - 1) {
					let sum = 0.0;

					// for each points, get the distance with the closest centroid already choosen
					for point in iterator(this) {
						let distance = <\KMeans\Point> point->getDistanceWith(<\KMeans\Point> point->getClosest(clusters));
						distances->offsetSet(point, distance);
						// let sum += distance;
						let sum = sum + distance;
					}

					// choose a new random point using a weighted probability distribution
					let sum = (double)rand(0, (int)sum);
					for point in iterator(this) {
						// let sum -= distances->offsetGet(point);
						let sum = sum - distances->offsetGet(point);
						if sum > 0 {
							continue;
						}
						let clusters[] = new Cluster(this, <\KMeans\Point> point->getCoordinates());
						break;
					}
				}

				break;
		}

		// assing all points to the first cluster
		clusters[0]->attachAll(this);

		return clusters;
	}

	protected function iterate(array clusters) -> bool
	{
		bool _continue = false;
		var cluster = null,
			point = null,
			closest = null,
			attach = null,
			detach = null;

		// migration storages
		let attach = new \SplObjectStorage;
		let detach = new \SplObjectStorage;

		// calculate proximity amongst points and clusters
		for cluster in clusters {
			for point in iterator(cluster) {
				// find the closest cluster
				let closest = point->getClosest(clusters);

				// move the point from its old cluster to its closest
				if unlikely closest === cluster {
					continue;
				}

				if !attach->offsetExists(closest) {
					attach->offsetSet(closest, new \SplObjectStorage);
				}

				if !detach->offsetExists(cluster) {
					detach->offsetSet(cluster, new \SplObjectStorage);
				}

				attach->offsetGet(closest)->attach(point);
				detach->offsetGet(cluster)->attach(point);

				let _continue = true;
			}
		}

		// perform points migrations
		for cluster in iterator(attach) {
			cluster->attachAll(attach->offsetGet(cluster));
		}

		for cluster in iterator(detach) {
			cluster->detachAll(detach->offsetGet(cluster));
		}

		// update all cluster's centroids
		for cluster in clusters {
			cluster->updateCentroid();
		}

		return _continue;
	}
}
