#pragma once

#include <stdint.h>

#include "bin.h"


uint32_t district_buffer_size(uint32_t id);
void add_and_clone_packet_to_district(uint32_t id, buffer_t* buffer);
buffer_t* pop_packet_from_district_into_new_buffer(uint32_t id);