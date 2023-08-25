#pragma once
#include<Windows.h>
class CLock
{
private:
    CRITICAL_SECTION m_section;
public:
    CLock(void)
    {
        InitializeCriticalSection(&m_section);
    }
    ~CLock(void)
    {
        DeleteCriticalSection(&m_section);
    }
    void lock()
    {
        EnterCriticalSection(&m_section);
    }
    void unLock()
    {
        LeaveCriticalSection(&m_section);
    }
};
class CAutoLock
{
private:
    CLock* m_pLock;
public:
    CAutoLock(CLock* pLock)
    {
        m_pLock = pLock;
        pLock->lock();
    }
    ~CAutoLock()
    {
        m_pLock->unLock();
    }
};
// ʾ��:
//CLock g_lock;
//void main()
//{
//    {
//        CAutoLock _lock(&g_lock);
//        //...
//    }// _lock �����ڴ˴�����, ����ʱ������
//}
