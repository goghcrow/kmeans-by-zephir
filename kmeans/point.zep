namespace KMeans;

// use \ArrayAccess;
// use \LogicException;

class Point implements \ArrayAccess
{
	protected space = null { get };
	protected dimention = 0;
	protected coordinates = [] { get };

	public function __construct(const <\KMeans\Space> space, const array! coordinates)
	{
		let this->space       = space;
		let this->dimention   = space->getDimention();
		let this->coordinates = coordinates;
	}

	public function toArray() -> array
	{
		return [
			"coordinates" : this->coordinates,
			"data" : isset this->space[this] ? this->space[this] : null
		];
	}

	public function getDistanceWith(const <\KMeans\Point> point, const bool! precise = true) -> double
	{
		int n = 0;
		double distance = 0.0,
			   difference = 0.0;

		if unlikely point->space !== this->space {
			throw new \LogicException("can only calculate distances from points in the same space");
		}

		for n in range(0, this->dimention - 1) {
			let difference = this->coordinates[n] - point->coordinates[n];
			let distance  += difference * difference;
		}

		return precise ? (double)sqrt(distance) : distance;
	}

	public function getClosest(const array! points) -> <\KMeans\Point>
	{
		var point = null,
			minPoint = null;
		double minDistance = -1,
			distance = 0;

		for point in points {
			let distance = (double)this->getDistanceWith(<\KMeans\Point> point, false);

			if unlikely minDistance === -1 {
				let minDistance = distance;
				let minPoint    = point;
				continue;
			}

			if distance < minDistance {
				let minDistance = distance;
				let minPoint    = point;
			}
		}

		return minPoint;
	}


	public function belongsTo(const <\KMeans\Space> space) -> bool
	{
		return this->space === space;
	}

	public function offsetExists(const int! offset) -> bool
	{
		return isset this->coordinates[offset];
	}

	public function offsetGet(const int! offset)
	{
		return this->coordinates[offset];
	}

	public function offsetSet(const int! offset, const var value) -> void
	{
		let this->coordinates[offset] = value;
	}

	public function offsetUnset(const int! offset) -> void
	{
		unset this->coordinates[offset];
	}
}
