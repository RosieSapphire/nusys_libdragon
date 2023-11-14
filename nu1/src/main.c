#include <GL/gl.h>
#include <GL/gl_integration.h>
#include <libdragon.h>

#include "vertex.h"

static surface_t *color_buffer;
static surface_t depth_buffer;

static struct vertex verts[] = {
	{{-64,  64, 5}, {0, 1}, {0x00, 0xFF, 0x00, 0xFF}},
	{{ 64,  64, 5}, {1, 1}, {0x00, 0x00, 0x00, 0xFF}},
	{{ 64, -64, 5}, {1, 0}, {0x00, 0x00, 0xFF, 0xFF}},
	{{-64, -64, 5}, {0, 0}, {0xFF, 0x00, 0x00, 0xFF}},
};

static u16 indis[] = {
	0, 2, 1, 3, 2, 0
};

static void _draw(void)
{
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

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
	display_init(RESOLUTION_320x240, DEPTH_32_BPP, 3,
	      GAMMA_NONE, ANTIALIAS_RESAMPLE);
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

	while (1)
	{
		color_buffer = display_get();
		rdpq_attach(color_buffer, &depth_buffer);
		gl_context_begin();

		_draw();

		gl_context_end();
		rdpq_detach_show();
	}

	return (0);
}
