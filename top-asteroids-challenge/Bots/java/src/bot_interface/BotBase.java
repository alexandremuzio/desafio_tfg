package bot_interface;

public abstract class BotBase extends Ship {

	public BotBase() {
		super(0);
	}
	
	public abstract Action process(GameState gamestate);
	
}
