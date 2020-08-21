<style>
img[alt=m] {
    max-width: 350px;
}
img[alt=b] {
    max-width: 500px;
}

</style>
# iBaye

步步高电子词典经典游戏 -- 三国霸业 多平台移植版本

目前已支持的平台：iOS/macOS/Windows/HTML5/微信小游戏

交流QQ群：526266208

## 开发环境配置

1. 安装emscripten

    Ubuntu

	```
    sudo apt install emscripten
	```

	或参考[官方文档](http://kripken.github.io/emscripten-site/docs/getting_started/downloads.html#platform-notes-installation-instructions-portable-sdk),
	或直接下载配置好开发环境的虚拟机：[百度云下载](https://pan.baidu.com/s/1eRFehjW)


2. 下载霸业源码，编译生成baye.js

```
    git clone https://git.oschina.net/bgwp/iBaye.git
    cd iBaye/js
    emconfigure cmake ../src
    make
```

## 游戏截图

### iOS原生版
![m](images/ios.jpg)

---
### 微信小游戏端
![b](images/wx.png)

---

### HTML5 - PC端
![](images/pc-h5.png)

---

### HTML5 - Mobile端
![m](images/ios-h5.png)

![m](images/ios-h5-k.png)

单手键盘：

![m](images/ios-h5-k2.png)
![m](images/ios-h5-k3.png)

---

### Windows版
![b](images/windows.png)

---

### macOS版
![b](images/macos.png)

---

### 支持高度定制mod，有丰富的修改mod

即使是农民，也能高度自由定制修改版本。

![b](images/mod1.png)
![b](images/mod2.png)
![m](images/mod.png)
