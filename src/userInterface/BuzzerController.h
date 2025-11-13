#pragma once

namespace ui {

class BuzzerController {
public:
    explicit BuzzerController(int buzzerPin);

    void playWarningTone();
    void playErrorTone();
    void stopTone();

    bool isPlaying() const;

private:
    int buzzerPin;
    bool playing;
};

} // namespace ui

