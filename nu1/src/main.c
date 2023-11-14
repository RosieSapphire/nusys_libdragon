#include <GL/gl.h>
#include <GL/gl_integration.h>
#include <libdragon.h>

#include "vector.h"
#include "vertex.h"

#define TICKRATE 24
#define DELTATIME (1.0f / (f32)TICKRATE)
#define DELTATICKS (DELTATIME * TICKS_PER_SECOND)

static surface_t *color_buffer;
static surface_t depth_buffer;

static f32 angle_last, angle;
static f32 pos_last[2], pos[2];
static u8 direction = 1;

static struct vertex verts[] = {
	{{-64,  64, 5}, {0, 1}, {0x00, 0xFF, 0x00, 0xFF}},
	{{ 64,  64, 5}, {1, 1}, {0x00, 0x00, 0x00, 0xFF}},
	{{ 64, -64, 5}, {1, 0}, {0x00, 0x00, 0xFF, 0xFF}},
	{{-64, -64, 5}, {0, 0}, {0xFF, 0x00, 0x00, 0xFF}},
};

static u16 indis[] = {
	0, 2, 1, 3, 2, 0
};

static void _draw(f32 subtick)
{
	f32 angle_lerp = angle_last + (angle - angle_last) * subtick;
	f32 pos_lerp[2] = {
		pos_last[0] + (pos[0] - pos_last[0]) * subtick,
		pos_last[1] + (pos[1] - pos_last[1]) * subtick,
	};

	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(pos_lerp[0], pos_lerp[1], 0);
	glRotatef(angle_lerp, 0, 0, 1);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glVertexPointer(3, GL_FLOAT, sizeof(struct vertex), verts->pos);
	glTexCoordPointer(2, GL_FLOAT, sizeof(struct vertex), verts->uv);
	glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(struct vertex), verts->col);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indis);

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}

int main(void)
{
	debug_init_isviewer();
	debug_init_usblog();
	display_init(RESOLUTION_320x240, DEPTH_32_BPP, 3,
	      GAMMA_NONE, ANTIALIAS_RESAMPLE);
	joypad_init();
	rdpq_init();
	gl_init();
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-160, 160, -120, 120, 1, 10);

	depth_buffer = surface_alloc(FMT_RGBA16, 320, 240);

	u32 ticks_last, ticks_now, ticks_delta, ticks_accum;

	ticks_last = get_ticks();
	ticks_accum = 0;
	pos[0] = pos[1] = pos_last[0] = pos_last[1] = 0;
	angle_last = angle = 0;
	while (1)
	{
		ticks_now = get_ticks();
		ticks_delta = TICKS_DISTANCE(ticks_last, ticks_now);
		ticks_accum += ticks_delta;
		ticks_last = ticks_now;

		while (ticks_accum >= DELTATICKS)
		{
			joypad_poll();
			const joypad_buttons_t press =
				joypad_get_buttons_pressed(JOYPAD_PORT_1);
			const joypad_buttons_t held =
				joypad_get_buttons_held(JOYPAD_PORT_1);

			/*
			 * Spinning
			 */
			direction ^= press.a;

			f32 angle_turn_amount = 2.4f + (4.8f * held.b);

			angle_last = angle;
			if (direction)
				angle += angle_turn_amount;
			else
				angle -= angle_turn_amount;

			/*
			 * Positioning
			 */
			pos_last[0] = pos[0];
			pos_last[1] = pos[1];
			pos[0] = joypad_get_inputs(JOYPAD_PORT_1).stick_x;
			pos[1] = joypad_get_inputs(JOYPAD_PORT_1).stick_y;

			ticks_accum -= DELTATICKS;
		}

		f32 subtick = (f32)ticks_accum / (f32)DELTATICKS;

		color_buffer = display_get();
		rdpq_attach(color_buffer, &depth_buffer);
		gl_context_begin();

		_draw(subtick);

		gl_context_end();
		rdpq_detach_show();
	}

	return (0);
}
