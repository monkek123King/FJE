# FJE_2
在第一版的基础上，加了两个设计模式：迭代器+策略模式

## 使用方法
`git clone -b FJE_2 https://github.com/monkek123King/FJE.git`

`cd FJE`

`cd build`

`sudo rm -r *`

`cmake ..`

`make`

执行矩阵风格，图标为默认的poker-face

`./fje -f ../json/example.json -s rectangle -i poker-face`

也可以自定义图标，在配置文件`IconJson/icon.json`中修改

`./fje -f ../json/example.json -s rectangle -i json_defined`
