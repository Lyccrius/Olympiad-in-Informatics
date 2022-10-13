class MinStack {
public:
    stack<int> value;
    stack<int> minimum;

    MinStack() {
        
    }
    
    void push(int x) {
        value.push(x);
        
        if (minimum.empty() || minimum.top()>x) {
            minimum.push(x);
        } else {
            minimum.push(minimum.top());
        }
    }
    
    void pop() {
        value.pop();
        minimum.pop();
    }
    
    int top() {
        return value.top();
    }
    
    int getMin() {
        return minimum.top();
    }
};