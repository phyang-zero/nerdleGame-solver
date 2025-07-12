# nerdleGame-solver

![C](https://img.shields.io/badge/language-C-blue.svg)
![Standard](https://img.shields.io/badge/standard-C99-green.svg)
![License](https://img.shields.io/badge/license-MIT-yellow.svg)
![Build](https://img.shields.io/badge/build-passing-brightgreen.svg)

本项目基于C语言实现了数学猜谜游戏Nerdle的本地复刻、手动解谜器和网页自动解谜器三大功能模块。

## 核心功能 

- **每日挑战** ：提供每日一题的本地游戏体验。  
- **手动解谜** ：用户输入颜色反馈，程序据此计算并推荐最优的下一步猜测。  
- **自动解谜** ：程序自动控制鼠标完成网页端解谜流程。

## 编译指引

```bash
gcc nerdleGame.c -o nerdle -std=c99
````

---

## 备注说明

* **自定义函数库** ：作为大一上学期的练手项目，按照课程要求未采用标准库函数，数学与字符串相关功能均由本人在 `myMath.h` 与 `myString.h` 中自定义实现。用户可根据需要替换为标准库函数以提升效率与兼容性。

* **网页自动解谜的局限性** ：自动解谜模块通过硬编码屏幕坐标与网页交互，导致其对环境高度依赖，难以在其他计算机上直接运行。用户需根据实际屏幕分辨率及网页布局自行调整坐标，或采用其他更通用的网页自动化方案。

> 备注：若非课程要求，本项目的自动解谜部分我更倾向于使用 Python 实现，以实现更强的灵活性和可维护性。😊
