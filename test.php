<?php
error_reporting(E_ALL);
gc_disable(); // 可以提升好多性能！！！
ini_set('memory_limit','128M');


// prepare 50 2D points to be clustered
$points = [
	[80,55],[86,59],[19,85],[41,47],[57,58],
	[76,22],[94,60],[13,93],[90,48],[52,54],
	[62,46],[88,44],[85,24],[63,14],[51,40],
	[75,31],[86,62],[81,95],[47,22],[43,95],
	[71,19],[17,65],[69,21],[59,60],[59,12],
	[15,22],[49,93],[56,35],[18,20],[39,59],
	[50,15],[81,36],[67,62],[32,15],[75,65],
	[10,47],[75,18],[13,45],[30,62],[95,79],
	[64,11],[92,14],[94,49],[39,13],[60,68],
	[62,10],[74,44],[37,42],[97,60],[47,73],
];


$x = 2000;
$start = microtime(true);
for ($i=0; $i < $x; $i++) {
	$space = new KMeans\Space(2);
	foreach ($points as $coordinates) {
		$space->addPoint($coordinates);
	}
	$clusters = $space->solve(3);
}
echo microtime(true) - $start;
echo PHP_EOL;
