import tensorflow as tf
from tensorflow.keras import Input, layers, Model


# one_tensor = tf.ones([1,256,256,3])

# print(one_tensor, type(one_tensor))
class subclass(Model):
    def __init__(self):
        super(subclass, self).__init__()
        self.conv = layers.Conv2D(28, 3, strides=1)

    def call(self, x):
        return self.conv(x)


def func_api():
    x = Input(shape=(24, 24, 3))
    y = layers.Conv2D(28, 3, strides=1)(x)
    return Model(inputs=[x], outputs=[y])

if __name__ == '__main__':
    func = func_api()
    func.summary()

    sub = subclass()
    sub.build(input_shape=(None, 24, 24, 3))
    sub.summary()

# class subclass(Model):
#     def __init__(self):
#         super(subclass, self).__init__()
#         self.conv = layers.Conv2D(28, 3, strides=1)

#     def call(self, x):
#         return self.conv(x)

#     def model(self):
#         x = Input(shape=(24, 24, 3))
#         return Model(inputs=[x], outputs=self.call(x))



# if __name__ == '__main__':
#     sub = subclass()
#     sub.model().summary()