
int entry(int argc, char **argv) {
	
	// This is how we (optionally) configure the window.
	// To see all the settable window properties, ctrl+f "struct Os_Window" in os_interface.c
	window.title = STR("INFINITY AD GAME");
	window.clear_color = hex_to_rgba(0x5b5553);

	Gfx_Image* player = load_image_from_disk(fixed_string("player.png"), get_heap_allocator());
	assert(player, "player sprite not loaded correctly.");

	Vector2 player_pos = v2(0, 0);

	float64 last_time = os_get_elapsed_seconds();

	while (!window.should_close) {
		reset_temporary_storage();
		
		float64 now = os_get_elapsed_seconds();
		float64 delta_t = now - last_time;
		last_time = now;
		
		os_update(); 

		if(is_key_just_pressed(KEY_ESCAPE)) {
			window.should_close = true;
		}

		Vector2 input_axis = v2(0, 0);
		if (is_key_down('A')) {
			input_axis.x -= 1.0;
		}
		if (is_key_down('D')) {
			input_axis.x += 1.0;
		}
		if (is_key_down('S')) {
			input_axis.y -= 1.0;
		}
		if (is_key_down('W')) {
			input_axis.y += 1.0;
		}

		//this line basically says: player_pos += (input_axis * speed * time since last frame);
		player_pos = v2_add(player_pos, v2_mulf(input_axis, 200.0 * delta_t));

		Matrix4 xform = m4_scalar(1.0);
		xform         = m4_translate(xform, v3(player_pos.x, player_pos.y, 0));
		draw_image_xform(player, xform, v2(250, 250), COLOR_GREEN);
		
		gfx_update();
	}

	return 0;
}