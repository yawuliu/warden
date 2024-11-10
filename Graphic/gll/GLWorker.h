#pragma once

#include <list>
#include "Storm/lock/win32Critical_Section.h"


class GLCommand;

class GLDevice;

class GLWorker {
public:
    // Static functions
    static void *Worker(void *);

    // Member variables
    GLDevice *m_Device;
    std::list<GLCommand *> m_Commands;
    win32Critical_Section m_Mutex1;
    win32Critical_Section m_Mutex2;
    CONDITION_VARIABLE m_Cond1;
    CONDITION_VARIABLE m_Cond2;
    HANDLE m_Thread;
//    pthread_mutex_t m_Mutex1;
//    pthread_mutex_t m_Mutex2;
//    pthread_cond_t m_Cond1;
//    pthread_cond_t m_Cond2;
//    pthread_t m_Thread;
    bool m_UnkA0;
    bool m_UnkA1;

    // Member functions
    GLWorker(GLDevice *);

    ~GLWorker();

    void Lock();

    void Send(GLCommand *);

    void Signal();

    void Unlock();

    void WaitOnGLObjects();
};


