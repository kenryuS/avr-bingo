// Non blocking timer with explicit types
template<typename Arg, typename Res>
class Timer {
    public:
        Timer(Callback<Arg, Res> f, Arg* arg, Res* res, unsigned long tout):
            cb_arg(arg),
            cb_res(res),
            timeout(tout)
        {
            last = 0;
            cb = f;
        }

        ~Timer() = default;

        void setTimeout(unsigned long t) {
            timeout = t;
        }

        unsigned long getTimeout() {
            return timeout;
        }

        void setArg(Arg* arg) {
            cb_arg = arg;
        }

        Arg* getArg() {
            return cb_arg;
        }

        void setRes(Res* res) {
            cb_res = res;
        }

        Res* getRes() {
            return cb_res;
        }

        void tick() {
            unsigned long curr = millis();

            if ((curr - last) <= timeout) return;

            (*cb)(cb_arg, cb_res);

            last = curr;
        };
    private:
        Callback<Arg, Res> *cb;

        Arg* cb_arg;
        Res* cb_res;
        unsigned long timeout;
        unsigned long last;
};
