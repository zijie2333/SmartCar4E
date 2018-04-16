#ifndef __BOX_FILTER_H
#define __BOX_FILTER_H

struct box_filter_params{
	int box_size;
	int frame;
	float *data;
};
void box_filter_init(int len, struct box_filter_params* filter);
float box_filter_update(float value, struct box_filter_params* filter);
void box_filter_release(struct box_filter_params* filter);

#endif //__BOX_FILTER_H
