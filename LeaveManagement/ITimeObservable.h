#pragma once
#include "ITimeObserver.h"

namespace LeaveManagement {

    using namespace System;

    public interface class ITimeObservable
    {
    public:
        // Method to add an observer
        void AddObserver(ITimeObserver^ observer);

        // Method to remove an observer
        void RemoveObserver(ITimeObserver^ observer);

        // Method to notify all observers
        void NotifyObservers();
    };
}
