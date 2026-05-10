#ifndef FMODTAPESTOPPLUGIN_ONEPOLELOWPASS_H
#define FMODTAPESTOPPLUGIN_ONEPOLELOWPASS_H

namespace tapestop::domain {

class OnePoleLowpass {
public:
    OnePoleLowpass();

    void setCutoff(float cutoff_hz, float sample_rate);
    float process(float input);
    void reset();

private:
    float prev_output_;
    float alpha_;
};

} // namespace tapestop::domain

#endif //FMODTAPESTOPPLUGIN_ONEPOLELOWPASS_H
