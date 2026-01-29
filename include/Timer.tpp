/*! @class Timer
 * @brief Non-blocking timer.
 * @param Arg Type of callback argument(s).
 * @param Res Type of callback return value(s).
 */
template<typename Arg, typename Res>
class Timer {
    public:
        /*! Constructor.
         * @param f Callback function to be executed.
         * @param arg Pointer to argument(s) of callback function with type Arg.
         * @param res Pointer to return(s) of callback function with type Res.
         * @param tout Time out of timer.
         */
        Timer(Callback<Arg, Res> f, Arg* arg, Res* res, unsigned long tout):
            cb_arg(arg),
            cb_res(res),
            timeout(tout)
        {
            last = 0;
            cb = f;
        }

        /*! Destructor. */
        ~Timer() = default;

        /*! Sets timeout.
         * @param t Target timeout.
         */
        void setTimeout(unsigned long t) {
            timeout = t;
        }

        /*! Gets timeout. */
        unsigned long getTimeout() {
            return timeout;
        }

        /*! Sets argument through pointer.
         * @param arg Pointer to argument(s).
         */
        void setArg(Arg* arg) {
            cb_arg = arg;
        }

        /*! Gets argument pointer. */
        Arg* getArg() {
            return cb_arg;
        }

        /*! Sets return through pointer.
         * @param res Pointer to return value(s).
         */
        void setRes(Res* res) {
            cb_res = res;
        }

        /*! Gets return value pointer. */
        Res* getRes() {
            return cb_res;
        }

        /*! Update timer and executes callback on timeout. */
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
