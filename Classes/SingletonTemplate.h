#pragma once

template <typename T>
class Singleton
{
public:
	static T* GetInstance()
	{
		if (s_mInstance == nullptr)
			s_mInstance = new T();

		return s_mInstance;
	}

	static void Destroy()
	{
		if (s_mInstance)
		{
			delete s_mInstance;
			s_mInstance = nullptr;
		}
	}

protected:
	Singleton(){};
	virtual ~Singleton(){};

private:
	static T* s_mInstance;
};

template <typename T>
T* Singleton<T>::s_mInstance = nullptr;
