~~~
zephir init
zephir builddev
zephir build

1. ArrayAccess接口不能用，要使用接口方法, eg. ->offsetGet()
2. Countable接口也不能直接在zep中使用，要使用 eg. ->count()
3. use 不能用
4. 最好先声明变量，并且赋初始值，否则可能发生段错误
5. Traversal 要用 for xx in iterator() 来遍历

// let centroid->coordinates[n] += <\KMeans\Point> point->coordinates[n];


切记：
php内置接口与spl类型的的各种方法不能用语法糖，不能用操作符重载

#返回结果可能是0
ulimit -c
当返回结果为0时，说明系统不会生成core文件，这个时候使用ulimit -c命令改变系统的默认设置
ulimit -c unlimited
#或者
ulimit -c n  #n大于0的数字

gdb php demo.php -c core
#进入之后显示很多东西，然后不停的 按 输入 bt回车，查看执行流程
#在gdb运行环境中，使用PHP的gdb调试脚本，其中/prefix/php-src-dir 是php的源码目录
source /prefix/php-src-dir/.gdbinit
#zbacktrace会更加精确到PHP的错误
zbacktrace

http://www.laruence.com/2011/06/23/2057.html
~~~
