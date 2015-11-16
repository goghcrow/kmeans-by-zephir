namespace KMeans;

// use \IteratorAggregate;
// use \Countable;
// use \SplObjectStorage;
// use \InvalidArgumentException;
// use \LogicException;

class Cluster extends Point implements \IteratorAggregate, \Countable
{
	protected space = null;
	protected points = null;

	public function __construct(const <\KMeans\Space> space, array coordinates)
	{
		parent::__construct(space, coordinates);
		let this->points = new \SplObjectStorage;
	}

	public function toArray() -> array
	{
		array points = [];
		var point = null;

		for point in iterator(this->points) {
			let points[] = <\KMeans\Point> point->toArray();
		}

		return [
			"centroid" : parent::toArray(),
			"points"   : points
		];
	}

	public function attach(const <\KMeans\Point> point) -> <\KMeans\Point>
	{
		if (point instanceof \KMeans\Cluster) {
			throw new \LogicException("cannot attach a cluster to another");
		}
		this->points->attach(point);
		return point;
	}

	public function detach(const <\KMeans\Point> point) -> <\KMeans\Point>
	{
		this->points->detach(point);
		return point;
	}

	public function attachAll(const <\SplObjectStorage> points) -> void
	{
		this->points->addAll(points);
	}

	public function detachAll(const <\SplObjectStorage> points) -> void
	{
		this->points->removeAll(points);
	}

	public function updateCentroid() -> void
	{
		int n = 0;
		var centroid = null,
			point = null;

		if this->points->count() === 0 {
			return;
		}

		let centroid = this->space->newPoint(array_fill(0, this->dimention, 0));

		for point in iterator(this->points) {
			for n in range(0, this->dimention - 1) {
				// FUCK
				// let centroid->coordinates[n] += <\KMeans\Point> point->coordinates[n];
				let centroid->coordinates[n] = centroid->coordinates[n] + <\KMeans\Point> point->coordinates[n];
			}
		}

		// echo centroid->coordinates[0];
		// echo PHP_EOL;
		// echo centroid->coordinates[1];
		// echo PHP_EOL;

		for n in range(0, this->dimention - 1) {
			let this->coordinates[n] = centroid->coordinates[n] / this->points->count();
		}
	}

	public function getIterator() -> <\Traversable>
	{
		return this->points;
	}

	public function count() -> int
	{
		return this->points->count();
	}
}
