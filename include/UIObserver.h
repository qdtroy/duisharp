#ifndef __UIOBSERVER_H__
#define __UIOBSERVER_H__

namespace duisharp {
	template <typename ReturnT, typename ParamT>
	class CReceiverImplBase;

	template <typename ReturnT, typename ParamT>
	class CObserverImplBase
	{
	public:
		virtual void AddReceiver(CReceiverImplBase<ReturnT, ParamT>* receiver) = 0;
		virtual void RemoveReceiver(CReceiverImplBase<ReturnT, ParamT>* receiver) = 0;
		virtual ReturnT Broadcast(ParamT param) = 0;
		virtual ReturnT Notify(ParamT param) = 0;
	};

	template <typename ReturnT, typename ParamT>
	class CReceiverImplBase
	{
	public:
		virtual void AddObserver(CObserverImplBase<ReturnT, ParamT>* observer) = 0;
		virtual void RemoveObserver() = 0;
		virtual ReturnT Receive(ParamT param) = 0;
		virtual ReturnT Respond(ParamT param, CObserverImplBase<ReturnT, ParamT>* observer) = 0;
	};

	template <typename ReturnT, typename ParamT>
	class CReceiverImpl;

	template <typename ReturnT, typename ParamT>
	class CObserverImpl : public CObserverImplBase<ReturnT, ParamT>
	{
		template <typename ReturnT, typename ParamT>
		friend class Iterator;

	public:
		CObserverImpl(){}
		virtual ~CObserverImpl(){}

	public:
		virtual void AddReceiver(CReceiverImplBase<ReturnT, ParamT>* receiver)
		{
			if (receiver == NULL)
				return;

			receivers_.Add(receiver);
			receiver->AddObserver(this);
		}

		virtual void RemoveReceiver(CReceiverImplBase<ReturnT, ParamT>* receiver)
		{
			if (receiver == NULL)
				return;

			receivers_.Remove(receivers_.Find(receiver));
		}

		virtual ReturnT Broadcast(ParamT param)
		{
			for (int it = 0; it < receivers_.GetSize(); ++it)
			{
				CReceiverImplBase<ReturnT, ParamT>* receiver = receivers_.GetAt(it);
				receiver->Receive(param);
			}

			return ReturnT();
		}

		virtual ReturnT RBroadcast(ParamT param)
		{
			for (int it = receivers_.GetSize() - 1; it >= 0; --it)
			{
				CReceiverImplBase<ReturnT, ParamT>* receiver = receivers_.GetAt(it);
				receiver->Receive(param);
			}

			return ReturnT();
		}

		virtual ReturnT Notify(ParamT param)
		{
			for (int it = 0; it < receivers_.GetSize(); ++it)
			{
				CReceiverImplBase<ReturnT, ParamT>* receiver = receivers_.GetAt(it);
				receiver->Respond(param, this);
			}

			return ReturnT();
		}

		template <typename ReturnT, typename ParamT>
		class Iterator
		{
			CObserverImpl<ReturnT, ParamT> & _tbl;
			int index;
			CReceiverImplBase<ReturnT, ParamT>* ptr;
		public:
			Iterator( CObserverImpl & table )
				: _tbl( table ), index(0), ptr(NULL)
			{}

			Iterator( const Iterator & v )
				: _tbl( v._tbl ), index(v.index), ptr(v.ptr)
			{}

			CReceiverImplBase<ReturnT, ParamT>* next()
			{
				if ( index >= _tbl.receivers_.GetSize() )
					return NULL;

				for ( ; index < _tbl.receivers_.GetSize(); )
				{
					ptr = _tbl.receivers_.GetAt(index++);
					if ( ptr ) return ptr;
				}
				return NULL;
			}
		};
	protected:
		CStdPtrArrayImpl<CReceiverImplBase<ReturnT, ParamT>*> receivers_;
	};


	template <typename ReturnT, typename ParamT>
	class CReceiverImpl : public CReceiverImplBase<ReturnT, ParamT>
	{
	public:
		CReceiverImpl(){}
		virtual ~CReceiverImpl(){}

	public:
		virtual void AddObserver(CObserverImplBase<ReturnT, ParamT>* observer)
		{
			observers_.Add(observer);
		}

		virtual void RemoveObserver()
		{
			observers_.Remove(observers_.Find((CObserverImplBase<ReturnT, ParamT>*)this));
		}

		virtual ReturnT Receive(ParamT param)
		{
			return ReturnT();
		}

		virtual ReturnT Respond(ParamT param, CObserverImplBase<ReturnT, ParamT>* observer)
		{
			return ReturnT();
		}

	protected:
		CStdPtrArrayImpl<CObserverImplBase<ReturnT, ParamT>*> observers_;
	};

} // namespace duisharp

#endif // __UIOBSERVER_H__