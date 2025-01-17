﻿#include "timeserver.h"
#include "timethread.h"
#include "dialog.h"
TimeServer::TimeServer(QObject *parent):QTcpServer(parent)
{
    dlg =(Dialog *)parent;
    connect(this,&TimeServer::newConnection,this,&TimeServer::slottest);
}
void TimeServer::incomingConnection(int socketDescriptor)
{
    TimeThread *thread = new TimeThread(socketDescriptor,0);	//(a)
    connect(thread,SIGNAL(finished()),dlg,SLOT(slotShow()));	//(b)
    connect(thread,SIGNAL(finished()),thread,SLOT(deleteLater()),
            Qt::DirectConnection);								//(c)
    thread->start();											//(d)
}
void TimeServer::slottest()
{
    QTcpSocket* test = nextPendingConnection();
    TimeThread *thread = new TimeThread(test->socketDescriptor(),0);	//(a)
    connect(thread,SIGNAL(finished()),dlg,SLOT(slotShow()));	//(b)
    connect(thread,SIGNAL(finished()),thread,SLOT(deleteLater()),
            Qt::DirectConnection);								//(c)
    thread->start();
}
