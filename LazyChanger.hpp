#ifndef LAZYCHANGER_HPP
#define LAZYCHANGER_HPP

template<typename Value>
class LazyChanger {
public:
    LazyChanger(Value initialValue = Value{}) : currentValue(initialValue) {}

    template<typename Callback>
    void update(Value newValue, const Callback& callback) {
        if (currentValue != newValue) {
            currentValue = newValue;
            callback(newValue);
        }
    }

    Value get() const { return currentValue; }

private:
    Value currentValue;
};


#endif // LAZYCHANGER_HPP
