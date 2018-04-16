#include "./box_filter.h"
#include <malloc.h>

void box_filter_init(int len, struct box_filter_params* filter)
{
	int i = 0;
	filter->box_size = len;
	filter->frame = 0;
	filter->data = (float*)malloc(filter->box_size * sizeof(float));
	for(i = 0;i < filter->box_size; i++) filter->data[i] = 0; 
}
float box_filter_update(float input, struct box_filter_params* filter)
{
	float output = 0.0;
	int i = 0;
	filter->data[filter->frame] = input;
	filter->frame = (filter->frame + 1) % filter->box_size;
	for(i = 0; i < filter->box_size; i++)
		output += filter->data[i];
	output /= filter->box_size;
	return output;
}
void box_filter_release(struct box_filter_params* filter)
{
	free(filter->data);
}
