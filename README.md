# CoinFlip
使用QT框架编写的一款翻硬币游戏，一共包含5个类

## 1、mainscene
### 构造函数
    窗口的初始化、开始的按钮、点击按钮后的主要场景的切换、返回场景的signal信号的返回按钮
### api
    paintEvent(QPaintEvent *)：重写绘图事件，利用Qpainter和QPixmap
    
## 2、MyPushButtion
### 构造函数
    有2个参数：默认显示图片路径和按下后显示图片路径，利用QPixmap来初始化按钮
### api
    zoom():利用QPropertyAnimation类实现动画：实现跳动

## 3、ChooseLevelScence
### 构造函数
    场景的初始化、返回按钮由一个signals：choose()发出，返回mainscence、创建选择关卡的按钮
### api
    paintEvent(QPaintEvent *)：重写绘图事件背景
    menuScence()：创建选择关卡按钮，每个按钮可以使用成员属性play指针初始化一个对应的场景，同时这儿也是对应场景返回的地方，记得指针置空

## 4、MyCoin
### 构造函数
    提供一个参数创建金币或者硬币的背景、初始化定时器、初始化翻转动作，当需要动作会执行翻转
### api
    changeFlag()：执行翻转，记得用标志isAnimaion禁止再次点击金币
    coinFlag()：翻转特效，利用定时器QTimer在30秒内执行翻转，利用的是QString str=QString(":/res/Coin000%1.png").arg(this->min++);然后加载pix.load(str);
    mousePressEvent(QMouseEvent *event)：重写鼠标事件，胜利的话就不能点击了

## 5、PlayScene
### 构造函数
  ·利用int参数初始化当前关卡、初始化背景、初始化菜单栏、调用成员函数back()显示返回按钮、调用成员函数showLevel()显示关卡、初始化二维数组为了判断翻转是否完成、初始化showCoin()显示金币、初始化showPic()胜利图片
### api
   paintEvent(QPaintEvent *)：重写绘图事件
   back()：返回选择界面，利用一个signals：back()信号发出，然后关闭这个界面
   showLevel()：显示当前关卡
   showCoin()：利用成员属性二维数组初始化16个金币或者银币，同时点击的话带动周围金币也要翻转
   flipCoin(MyCoin *coin)：实现周围金币的翻转，同时利用二维数组判断是否获胜
   showPic()：直接创建好图片
   turnPic()：一旦胜利直接将图片放下

## else
    声效：利用QSound
    
