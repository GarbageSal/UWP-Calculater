#pragma once

#include "MainPage.g.h"

using namespace winrt;
using namespace Windows::UI::Xaml;
using namespace Windows::Foundation;
using namespace Collections;
using namespace Controls;

namespace winrt::Calculator::implementation {
    struct MainPage : MainPageT<MainPage> {
        bool isAdjusted = false;
        bool isNum = true;
        bool isEnd = false;
        std::string exp;
        MainPage();
        void resultUpdate(std::string result);
        void cal();
        void clear();
        TextBlock makeExpression(std::string text, double leftMargin);
        void expressionPanel_SizeChanged(IInspectable const& sender, SizeChangedEventArgs const& e);
        void openParenButton_Click(IInspectable const& sender, RoutedEventArgs const& e);
        void closeParenButton_Click(IInspectable const& sender, RoutedEventArgs const& e);
        void clearEntryButton_Click(IInspectable const& sender, RoutedEventArgs const& e);
        void clearButton_Click(IInspectable const& sender, RoutedEventArgs const& e);
        void logicalAndButton_Click(IInspectable const& sender, RoutedEventArgs const& e);
        void logicalOrButton_Click(IInspectable const& sender, RoutedEventArgs const& e);
        void logicalNotButton_Click(IInspectable const& sender, RoutedEventArgs const& e);
        void divideButton_Click(IInspectable const& sender, RoutedEventArgs const& e);
        void numButton_Click(IInspectable const& sender, RoutedEventArgs const& e);
        void multiplyButton_Click(IInspectable const& sender, RoutedEventArgs const& e);
        void minusButton_Click(IInspectable const& sender, RoutedEventArgs const& e);
        void plusButton_Click(IInspectable const& sender, RoutedEventArgs const& e);
        void negateButton_Click(IInspectable const& sender, RoutedEventArgs const& e);
        void backSpaceButton_Click(IInspectable const& sender, RoutedEventArgs const& e);
        void equalButton_Click(IInspectable const& sender, RoutedEventArgs const& e);
        void resultsBlock_SizeChanged(IInspectable const& sender, SizeChangedEventArgs const& e);
    };
}

namespace winrt::Calculator::factory_implementation {
    struct MainPage : MainPageT<MainPage, implementation::MainPage> {
    };
}
