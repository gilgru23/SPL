package bgu.spl.mics;
import java.util.concurrent.*;

/**
 * The {@link MessageBrokerImpl class is the implementation of the MessageBroker interface.
 * Write your implementation here!
 * Only private fields and methods can be added to this class.
 */
public class MessageBrokerImpl implements MessageBroker {
	private static MessageBrokerImpl broker;
	private static ConcurrentHashMap<Class<? extends Event<?>>, ConcurrentLinkedQueue<Subscriber>> eventSubMap;
	private ConcurrentHashMap<Class<? extends Broadcast>, ConcurrentSkipListSet<Subscriber>> broadcastSubMap;
	private ConcurrentHashMap<Event,Future> eventMap;
	private ConcurrentHashMap<Subscriber,ConcurrentLinkedQueue<Message>> subsQueueMap;
	//singelton Holder constructor
	private MessageBrokerImpl() {
		eventSubMap = new ConcurrentHashMap<>();
	}

	private static class SingletonHolder {
		private static MessageBrokerImpl
				instance = new MessageBrokerImpl();
	}

	public static MessageBrokerImpl getInstance() {
		return SingletonHolder.instance;
	}
//
	@Override
	public <T> void subscribeEvent(Class<? extends Event<T>> type, Subscriber m) {
		ConcurrentLinkedQueue<Subscriber> q =new ConcurrentLinkedQueue<>();
		ConcurrentLinkedQueue<Subscriber> temp =null;
		try{
			temp= eventSubMap.putIfAbsent(type,q);
		}
		catch (Exception e){}
		if(temp==null)
		//TODO: init all
		{
			q.add(m);
		}
		else {
			if(!temp.contains(m))
			temp.add(m);
		}
	}

	@Override
	public void subscribeBroadcast(Class<? extends Broadcast> type, Subscriber m) {
		//ConcurrentSkipListSet
		ConcurrentSkipListSet<Subscriber> list =new ConcurrentSkipListSet<>();
		ConcurrentSkipListSet<Subscriber> temp =null;
		try{
			temp= broadcastSubMap.putIfAbsent(type,list);
		}
		catch (Exception e){}
		if(temp==null)
		{
			list.add(m);
		}
		else {
			if(!temp.contains(m))
				temp.add(m);
		}
	}

	@Override
	public <T> void complete(Event<T> e, T result) {
		if (e==null)
		{
			//TODO: decide what do do in case event is null
		}
		Future f = eventMap.get(e);
		if(f==null)
		{
			//TODO: decide what do do in case event is not found
		}
		else
		{
			f.resolve(result);
		}
	}

	@Override
	public void sendBroadcast(Broadcast b) {
		if (b==null)
		{
			//TODO: throw exception
		}
		ConcurrentSkipListSet<Subscriber> list = broadcastSubMap.get(b.getClass());
		if (list!=null)
		{
			for (Subscriber s:list) {
				ConcurrentLinkedQueue<Message> q= subsQueueMap.get(s);
				if(q==null)
				{
					//TODO: wait?
				}
				else
				{
					q.offer(b);
				}
			}
		}
		else//list==null
		{
			//TODO:bom  - see what needs to be done in case we attempt to read from
			//TODO:			broadcastSubMap while it is being modified
		}
	}

	
	@Override
	public <T> Future<T> sendEvent(Event<T> e) {
		Future f = new Future();
		eventMap.put(e,f);
		assignEvent(e);
		return f;
	}

	private <T> void assignEvent(Event<T> e) {
		if (e==null)
		{
			//TODO: throw exception
		}
		ConcurrentLinkedQueue<Subscriber> q = eventSubMap.get(e.getClass());
		if (q!=null)
		{
			//problem here is that n publishers threads might wanna
			//pull the same subscriber from the eventSubMap on the same queue
			//when q's size is only n-1 ;
			synchronized(q) //TODO:find more efficient way
			{
				Subscriber s=q.poll();
				if (s!=null)
				{
					ConcurrentLinkedQueue<Message> suberQ = subsQueueMap.get(s);
					if (suberQ==null)
					{
						//TODO: see what this part has to do with awaitMessage()
					}
					else
					{
						suberQ.offer(e);
					}
					q.offer(s);
				}
				else //s==null
				{
					//TODO: make thread wait until a subscriber is added to the queue
				}
			}
		}
		else//q==null
		{
			//TODO: throw exception probably
		}
	}

	@Override
	public void register(Subscriber m) {
		if(m==null)
		{
			//TODO:throw exception
		}
		subsQueueMap.putIfAbsent(m,new ConcurrentLinkedQueue<>());
	}

	@Override
	public void unregister(Subscriber m) {
		if(m==null)
		{
			//TODO:throw exception
		}
		//delete the subscriber and his message queue
		subsQueueMap.remove(m);
		//TODO:check if the deletion is safe
		//delete the subscriber from the event map
		boolean found=false;
		for(Class<? extends Event<?>> e : eventSubMap.keySet())
		{
			ConcurrentLinkedQueue<Subscriber> subs = eventSubMap.get(e);
			for(Subscriber s : subs)
			{
				if(s==m)//TODO:check if we can find the subscriber by refrence
				{
					found=true;
					break;
				}
			}
			if(found)
				break;
		}
		//delete the subscriber from the broadcast map
		found=false;
		for(Class<? extends Broadcast> b: broadcastSubMap.keySet())
		{
			ConcurrentSkipListSet<Subscriber> subs = broadcastSubMap.get(b);
			for(Subscriber s : subs)
			{
				if(s==m)//TODO:check if we can find the subscriber by refrence
				{
					found=true;
					break;
				}
			}
			if(found)
				break;
		}
	}

	@Override
	public  Message awaitMessage(Subscriber m) throws InterruptedException {
		if (m == null)
		{
			//TODO:throw exception
		}
		ConcurrentLinkedQueue<Message> messages = subsQueueMap.get(m);
		if(messages==null)
		{
		  //TODO::throw exception
		}
		Message output;
		synchronized (messages) {
			while (messages.isEmpty()) {
				messages.wait(1000);
			}
			 output = messages.poll();
			messages.notifyAll();
		}
		//TODO:check what to do if output is null
		return output;
	}
	

}
