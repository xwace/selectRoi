项目工程右键->添加现有项->添加ui文件到源文件->编译运行生成ui_x.h文件->复制一份ui_x.h并重命名为qrc_x.cpp。
该项目涉及：
1.mousePressEvent,mouseMoveEvent,mouseReleaseEvent重载override捕捉鼠标动作 
2.private slots: void on_pB_x_clicked()接收界面的按键操作信号 
3.connect(trackThread,SIGNAL(trackThread::send_velocity(int),ui.RobotVe,SLOTS(RobotVe::display(int))信号槽函数的连接。emit trackThread::send_velocity触发发送信号,返回扫地机速度。
4.开启多线程处理业务逻辑：计时。
