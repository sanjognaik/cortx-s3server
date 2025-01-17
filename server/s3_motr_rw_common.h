/*
 * Copyright (c) 2020 Seagate Technology LLC and/or its Affiliates
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * For any questions about this software or licensing,
 * please email opensource@seagate.com or cortx-questions@seagate.com.
 *
 */

#pragma once

#ifndef __S3_SERVER_S3_MOTR_RW_COMMON_H__
#define __S3_SERVER_S3_MOTR_RW_COMMON_H__

#include "s3_common.h"

EXTERN_C_BLOCK_BEGIN
#include "motr/init.h"
#include "module/instance.h"

#include "motr/client.h"
#include "lib/cksum.h"
/* libevhtp */
#include <evhtp.h>

void motr_op_done_on_main_thread(evutil_socket_t, short events,
                                 void *user_data);

void s3_motr_op_stable(struct m0_op *op);

void s3_motr_op_failed(struct m0_op *op);
// funtion is to handle motr pre launch opeariton failures in async way
void s3_motr_op_pre_launch_failure(void *application_context, int rc);
void s3_motr_dummy_op_stable(evutil_socket_t, short events, void *user_data);

void s3_motr_dummy_op_failed(evutil_socket_t, short events, void *user_data);

EXTERN_C_BLOCK_END

// Motr operation context from application perspective.
// When multiple ops are launched in single call,
// op_index_in_launch indicates index in ops array to
// identify specific operation.
struct s3_motr_context_obj {
  int op_index_in_launch;
  void *application_context;
  int is_fake_failure;  // 0 = false, 1 = true
};

#endif
