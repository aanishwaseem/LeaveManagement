#pragma once

#include "ITimeObserver.h"
#include "ITimeObservable.h"



namespace LeaveManagement {
    using namespace System;

    public ref class MyTime : public ITimeObservable
    {
    private:
        static MyTime^ instance = nullptr; // Static field for Singleton instance
        static System::Collections::Generic::List<ITimeObserver^>^ observers; // List of observers
        MyTime()
        {
            if (observers == nullptr)
            {
                observers = gcnew System::Collections::Generic::List<ITimeObserver^>();
            }

            day = 1;
            month = 1;
            year = 2024;
        }

    public:
        int day;
        int month;
        int year;

        // Private constructor to prevent direct instantiation

        // Singleton method to get the instance
        static MyTime^ GetInstance()
        {
            if (instance == nullptr)
            {
                instance = gcnew MyTime();
            }
            return instance;
        }

        // Implement the AddObserver method
        virtual void AddObserver(ITimeObserver^ observer)
        {
            observers->Add(observer);
        }

        // Implement the RemoveObserver method
        virtual void RemoveObserver(ITimeObserver^ observer)
        {
            observers->Remove(observer);
        }

        // Implement the NotifyObservers method
        virtual void NotifyObservers()
        {
            for each (ITimeObserver ^ observer in observers)
            {
                observer->Update(GetDate()); // Notify each observer
            }
        }

        // Move to the next day
        void NextDay()
        {
            NotifyObservers();

            day++;

            // Handle month and leap year logic
            if ((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && day > 31) {
                day = 1;
                month++;
            }
            else if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
                day = 1;
                month++;
            }
            else if (month == 2 && (day > 28 && !IsLeapYear(year) || day > 29)) {
                day = 1;
                month++;
            }

            if (month > 12) {
                month = 1;
                year++;
            }

            // Notify all observers about the change
        }

        String^ GetDate()
        {
            return day.ToString() + "-" + month.ToString() + "-" + year.ToString();
        }

    private:
        // Leap year check
        bool IsLeapYear(int year)
        {
            return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
        }
    };

    // Example usage of Singleton:
    public ref class MyAppController
    {
    public:
        void NextDay()
        {
            MyTime^ myTime = MyTime::GetInstance(); // Get the singleton instance
            myTime->NextDay(); // Call NextDay using the singleton instance
        }
    };
}
