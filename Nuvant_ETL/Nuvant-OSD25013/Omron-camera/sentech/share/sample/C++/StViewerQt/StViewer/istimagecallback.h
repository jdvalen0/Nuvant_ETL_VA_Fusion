#ifndef ISTIMAGECALLBACK_H
#define ISTIMAGECALLBACK_H

struct IStImageCallback
{
    virtual void OnIStImage(StApi::IStImage *) = 0;
};

struct IStImageCallbackRegister
{
    virtual void Add(IStImageCallback *pIStImageCallback) = 0;
    virtual void Remove(IStImageCallback *pIStImageCallback) = 0;
};

class CIStImageCallbackList final : public IStImageCallback, public IStImageCallbackRegister
{
public:
	CIStImageCallbackList()
	{
	}

	~CIStImageCallbackList()
	{
	}

    // Implementation of IStImageCallbackRegister
    void Add(IStImageCallback *pIStImageCallback) override
	{
		GenApi::AutoLock objAuto(m_objLock);
		m_vecCallbackList.push_back(pIStImageCallback);
	}

    // Implementation of IStImageCallbackRegister
    void Remove(IStImageCallback *pIStImageCallback) override
	{
		GenApi::AutoLock objAuto(m_objLock);
		for (std::vector<IStImageCallback*>::iterator itr = m_vecCallbackList.begin(); itr != m_vecCallbackList.end(); ++itr)
		{
			if (*itr == pIStImageCallback)
			{
				m_vecCallbackList.erase(itr);
				break;
			}
		}
	}

    // Implementation of IStImageCallback
	void OnIStImage(StApi::IStImage *pIStImage)
	{
		GenApi::AutoLock objAuto(m_objLock);
		for (std::vector<IStImageCallback*>::iterator itr = m_vecCallbackList.begin(); itr != m_vecCallbackList.end(); ++itr)
		{
			(*itr)->OnIStImage(pIStImage);
		}
	}

protected:
	GenApi::CLock m_objLock;
	std::vector<IStImageCallback*> m_vecCallbackList;
};

#endif
