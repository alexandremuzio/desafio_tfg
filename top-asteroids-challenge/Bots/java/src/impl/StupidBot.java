package impl;

import java.io.IOException;

import bot_interface.Action;
import bot_interface.BotBase;
import bot_interface.GameState;

public class StupidBot extends BotBase {

	public Action process(GameState gamestate) {
		return new Action(0, 1, 1, 0); 
	}
	
	public static void main(String[] args) throws IOException {
		GameState game = new GameState(new StupidBot());
		game.connect();
	}
}
