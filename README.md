# kmeans-by-zephir
事实证明，zephir语言写的扩展，性能还是很坑爹的

第一次用，翻译的算法，果然不能把用面向对象的姿势写的代码翻译成c语言

zephir官网 http://zephir-lang.com/

收获还是有的，在大量对象存在，且有大量交叉引用的情况下，果断关闭gc，性能提升明显
