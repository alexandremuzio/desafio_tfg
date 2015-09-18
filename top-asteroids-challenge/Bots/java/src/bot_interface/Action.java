package bot_interface;

public class Action {

	public float thrust;
	public float sideThrustFront;
	public float sideThrustBack;
	public int shoot;
	
	public Action(float thrust, float sideThrustFront, float sideThrustBack, int shoot) {
		super();
		this.thrust = thrust;
		this.sideThrustFront = sideThrustFront;
		this.sideThrustBack = sideThrustBack;
		this.shoot = shoot;
	}
	
}
