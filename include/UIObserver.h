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

			receivers_.push_back(receiver);
			receiver->AddObserver(this);
		}

		virtual void RemoveReceiver(CReceiverImplBase<ReturnT, ParamT>* receiver)
		{
			if (receiver == NULL)
				return;

			ReceiversVector::iterator it = receivers_.begin();
			for (; it != receivers_.end(); ++it)
			{
				if (*it == receiver)
				{
					receivers_.erase(it);
					break;
				}
			}
		}

		virtual ReturnT Broadcast(ParamT param)
		{
			ReceiversVector::iterator it = receivers_.begin();
			for (; it != receivers_.end(); ++it)
			{
				(*it)->Receive(param);
			}

			return ReturnT();
		}

		virtual ReturnT RBroadcast(ParamT param)
		{
			ReceiversVector::reverse_iterator it = receivers_.rbegin();
			for (; it != receivers_.rend(); ++it)
			{
				(*it)->Receive(param);
			}

			return ReturnT();
		}

		virtual ReturnT Notify(ParamT param)
		{
			ReceiversVector::iterator it = receivers_.begin();
			for (; it != receivers_.end(); ++it)
			{
				(*it)->Respond(param, this);
			}

			return ReturnT();
		}

		template <typename ReturnT, typename ParamT>
		class Iterator
		{
			CObserverImpl<ReturnT, ParamT> & _tbl;
			size_t index;
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
				if ( index >= _tbl.receivers_.size() )
					return NULL;

				for ( ; index < _tbl.receivers_.size(); )
				{
					ptr = _tbl.receivers_[ index++ ];
					if ( ptr )
						return ptr;
				}
				return NULL;
			}
		};
	protected:
		typedef std::vector<CReceiverImplBase<ReturnT, ParamT>*> ReceiversVector;
		ReceiversVector receivers_;
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
			observers_.push_back(observer);
		}

		virtual void RemoveObserver()
		{
			ObserversVector::iterator it = observers_.begin();
			for (; it != observers_.end(); ++it)
			{
				(*it)->RemoveReceiver(this);
			}
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
		typedef std::vector<CObserverImplBase<ReturnT, ParamT>*> ObserversVector;
		ObserversVector observers_;
	};

} // namespace duisharp

#endif // __UIOBSERVER_H__