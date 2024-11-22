#pragma once



namespace LeaveManagement {

    using namespace System;

    public interface class ITimeObserver
    {
    public:
        // Method called when the observable (MyTime) updates
        void Update(String^);
    };
}
