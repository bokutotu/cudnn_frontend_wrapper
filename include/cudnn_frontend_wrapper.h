#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>

typedef enum {
    SUCCESS = 0,
    FAILURE = 1,
    INVALID_VALUE = 2,
    NOT_SUPPORTED = 3,
    // Add more error codes as needed
} CudnnFrontendError_t;

typedef enum {
    DATA_TYPE_HALF,
    DATA_TYPE_FLOAT,
    DATA_TYPE_DOUBLE,
    // Add more as needed
} CudnnFrontendDataType_t;

typedef struct {
    size_t num_dims;
    int64_t dims[8];
    int64_t strides[8];
} CudnnTensorShapeStride;

typedef struct BatchNormDescriptor BatchNormDescriptor;

typedef struct {
    void* X;
    void* mean;
    void* inv_variance;
    void* scale;
    void* bias;
    void* peer_stats_0;
    void* peer_stats_1;
    void* prev_running_mean;
    void* prev_running_var;
    void* next_running_mean;
    void* next_running_var;
    void* Y;
} BatchNormExecutionBuffers;

CudnnFrontendError_t create_batch_norm_descriptor(BatchNormDescriptor** desc, 
                                                  CudnnFrontendDataType_t data_type, 
                                                  const CudnnTensorShapeStride* shape,
                                                  bool is_training);

CudnnFrontendError_t set_batch_norm_epsilon(BatchNormDescriptor* desc, float epsilon);

CudnnFrontendError_t set_batch_norm_momentum(BatchNormDescriptor* desc, float momentum);

CudnnFrontendError_t execute_batch_norm_forward_training(BatchNormDescriptor* desc, 
                                                         BatchNormExecutionBuffers* buffers);

typedef struct BatchNormBackwardDataDescriptor BatchNormBackwardDataDescriptor;

typedef struct {
    void* dY;
    void* X;
    void* mean;
    void* inv_variance;
    void* scale;
    void* dX;
} BatchNormBackwardDataExecutionBuffers;

CudnnFrontendError_t create_batch_norm_backward_data_descriptor(BatchNormBackwardDataDescriptor** desc, 
                                                                CudnnFrontendDataType_t data_type, 
                                                                const CudnnTensorShapeStride* shape);

CudnnFrontendError_t execute_batch_norm_backward_data(BatchNormBackwardDataDescriptor* desc,
                                                      BatchNormBackwardDataExecutionBuffers* buffers);

typedef struct ConvDescriptor ConvDescriptor;

#ifdef __cplusplus
}
#endif