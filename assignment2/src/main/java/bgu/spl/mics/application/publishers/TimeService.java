package bgu.spl.mics.application.publishers;

import bgu.spl.mics.Publisher;
import bgu.spl.mics.application.messages.TickBroadcast;

import java.util.concurrent.atomic.AtomicInteger;

/**
 * TimeService is the global system timer There is only one instance of this Publisher.
 * It keeps track of the amount of ticks passed since initialization and notifies
 * all other subscribers about the current time tick using {@link TickBroadcast}.
 * This class may not hold references for objects which it is not responsible for.
 * 
 * You can add private fields and public methods to this class.
 * You MAY change constructor signatures and even add new public constructors.
 */
public class TimeService extends Publisher {
	private int duration;
	private int currentTime;
	public TimeService(int duration) {
		super("TimeService");
		this.duration=duration;
	}

	@Override
	protected void initialize() {
		currentTime=0;
		
	}

	@Override
	public void run() {
		initialize();
		while(currentTime<duration)
		{
			getSimplePublisher().sendBroadcast(new TickBroadcast(currentTime));
			currentTime++;
			try {
				wait(100);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
	}

}
