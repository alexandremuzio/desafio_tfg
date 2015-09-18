package bot_interface;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;

public class GameState {
	
	private BotBase bot;
	private HashMap<Integer, Ship> ships;
	private HashMap<Integer, Rock> rocks;
	private HashMap<Integer, Laser> lasers;
	private HashSet<Integer> missing;
	
	private int tick;
	private float timestep;
	private float arenaRadius;
	private Action lastAction;
	
	public GameState(BotBase bot) {
		super();
		this.bot = bot;
		ships = new HashMap<Integer, Ship>();
		rocks = new HashMap<Integer, Rock>();
		lasers = new HashMap<Integer, Laser>();
		missing = new HashSet<Integer>();
		lastAction = new Action(0.0f, 0.0f, 0.0f, 0);
	}
	
	Ship getShip(int uid) {
		if (!ships.containsKey(uid)) {
			ships.put(uid, new Ship(uid));
		}
		missing.remove(uid);
		return ships.get(uid);
	}
	
	Rock getRock(int uid) {
		if (!rocks.containsKey(uid)) {
			rocks.put(uid, new Rock(uid));
		}
		missing.remove(uid);
		return rocks.get(uid);
	}
	
	Laser getLaser(int uid) {
		if (!lasers.containsKey(uid)) {
			lasers.put(uid, new Laser(uid));
		}
		missing.remove(uid);
		return lasers.get(uid);
	}
	
	public void log(String message) {
		System.err.print(message + "\r\n");
		System.err.flush();
	}
	
	void read(String data) {
		String[] tokens = data.trim().split("\\ ");
		
		if (tokens[0].equals("ship")) {
			getShip(Integer.parseInt(tokens[1])).update(
					Float.parseFloat(tokens[2]),
					Float.parseFloat(tokens[3]),
					Float.parseFloat(tokens[4]),
					Float.parseFloat(tokens[5]),
					Float.parseFloat(tokens[6]),
					Float.parseFloat(tokens[7]),
					Float.parseFloat(tokens[8]),
					Float.parseFloat(tokens[9]),
					Integer.parseInt(tokens[10])
			);
		} else if (tokens[0].equals("rock")) {
			getRock(Integer.parseInt(tokens[1])).update(
					Float.parseFloat(tokens[2]),
					Float.parseFloat(tokens[3]),
					Float.parseFloat(tokens[4]),
					Float.parseFloat(tokens[5]),
					Float.parseFloat(tokens[6])
			);
		} else if (tokens[0].equals("laser")) {
			getLaser(Integer.parseInt(tokens[1])).update(
					Float.parseFloat(tokens[2]),
					Float.parseFloat(tokens[3]),
					Float.parseFloat(tokens[4]),
					Float.parseFloat(tokens[5]),
					Float.parseFloat(tokens[6]),
					Float.parseFloat(tokens[7]),
					Integer.parseInt(tokens[8])
			);
		} else if (tokens[0].equals("tick")) {
			tick = Integer.parseInt(tokens[1]);
		} else if (tokens[0].equals("arenaRadius")) {
			arenaRadius = Float.parseFloat(tokens[1]);
		} else if (tokens[0].equals("timestep")) {
			timestep = Float.parseFloat(tokens[1]);
		} else if (tokens[0].equals("uid")) {
			bot.uid = Integer.parseInt(tokens[1]);
			ships.put(bot.uid, bot);
		}
	}
	
	public void connect() throws IOException {
		
		BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
		
		log("Bot Loaded");
		
		while(true) {
			
			for(int miss : ships.keySet()) {
				missing.add(miss);
			}
			for(int miss : rocks.keySet()) {
				missing.add(miss);
			}
			for(int miss : lasers.keySet()) {
				missing.add(miss);
			}
			
			String frameData = reader.readLine().trim();
			for(String data : frameData.split("\\|")) {
				read(data);
			}
			
			for(int miss : missing) {
				ships.remove(miss);
				rocks.remove(miss);
				lasers.remove(miss);
			}
			missing.clear();
			
			try {
				lastAction = bot.process(this);
			} catch(Exception e) {
				System.err.print(e.getMessage() + "\r\n");
				System.err.flush();
			}
			
			System.out.print("" + lastAction.thrust + " " + lastAction.sideThrustFront + " " + lastAction.sideThrustBack + " " + lastAction.shoot + "\r\n");
			System.out.flush();
		}
		
	}

	public BotBase getBot() {
		return bot;
	}

	public Map<Integer, Ship> getShips() {
		return ships;
	}

	public Map<Integer, Rock> getRocks() {
		return rocks;
	}

	public Map<Integer, Laser> getLasers() {
		return lasers;
	}

	public int getTick() {
		return tick;
	}

	public float getTimestep() {
		return timestep;
	}

	public float getArenaRadius() {
		return arenaRadius;
	}
}
