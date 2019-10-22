#include "MainWindow.hpp"
#include <QApplication>
#include <QtDebug>
#include <tensorflow/lite/interpreter.h>
#include <tensorflow/lite/kernels/register.h>
#include <tensorflow/lite/model.h>

MainWindow::MainWindow() {
    auto modelPath = QApplication::applicationDirPath() + "/resources/deeplabv3_257_mv_gpu.tflite";
    auto model = tflite::FlatBufferModel::BuildFromFile(modelPath.toUtf8().data());

    std::unique_ptr<tflite::Interpreter> interpreter;

    tflite::ops::builtin::BuiltinOpResolver resolver;
    tflite::InterpreterBuilder(*model.get(), resolver)(&interpreter);

    interpreter->AllocateTensors();

    auto inputTensor = interpreter->tensor(interpreter->inputs()[0]);
    int inputBatchSize = inputTensor->dims->data[0];
    int inputWidth = inputTensor->dims->data[1];
    int inputHeight = inputTensor->dims->data[2];
    int inputChannelCount = inputTensor->dims->data[3];

    qDebug() << "input batch size:" << inputBatchSize;
    qDebug() << "input width:" << inputWidth;
    qDebug() << "input height:" << inputHeight;
    qDebug() << "input channel count:" << inputChannelCount;

    auto outputTensor = interpreter->tensor(interpreter->outputs()[0]);
    int outputBatchSize = outputTensor->dims->data[0];
    int outputWidth = outputTensor->dims->data[1];
    int outputHeight = outputTensor->dims->data[2];
    int outputChannelCount = outputTensor->dims->data[3];

    qDebug() << outputTensor->dims->size;
    qDebug() << "output batch size:" << outputBatchSize;
    qDebug() << "output width:" << outputWidth;
    qDebug() << "output height:" << outputHeight;
    qDebug() << "output channel count:" << outputChannelCount;
}
