#include "pch.h"
#include "MainPage.h"
#include "MainPage.g.cpp"
#include "winrt/Windows.UI.Xaml.Media.h"
#include "CalculatorCore.h"

using namespace winrt;
using namespace Windows::UI::Xaml;
using namespace Windows::Foundation;
using namespace Controls;

namespace winrt::Calculator::implementation {

    MainPage::MainPage() {
        InitializeComponent();
        resultUpdate("0");
    }

    void MainPage::resultUpdate(std::string result) {
        this->isAdjusted = false;
        resultsBlock().Text(to_hstring(result));
    }

    void MainPage::cal() {
        try {
            auto result = calculator(std::stringstream(this->exp + "\n"));
            resultUpdate(result.convert_to<std::string>());
        } catch (const std::exception& e) {
            resultUpdate(e.what());
        }
    }

    void MainPage::clear() {
        this->isNum = true;
        this->exp.clear();
        resultUpdate("0");
        expressionPanel().Children().Clear();
    }

    TextBlock MainPage::makeExpression(std::string text, double leftMargin = 2) {
        auto expression = TextBlock();
        expression.FontSize(14);
        expression.Text(to_hstring(text));
        expression.Margin(Thickness{leftMargin,0,0,0});
        return expression;
    }

    void MainPage::expressionPanel_SizeChanged(IInspectable const& sender, SizeChangedEventArgs const& e) {
        expressionViewer().ScrollToHorizontalOffset(sender.as<StackPanel>().ActualWidth());
    }


    void MainPage::openParenButton_Click(IInspectable const& sender, RoutedEventArgs const& e) {
        if (this->isEnd) {
            clear();
            this->isEnd = false;
        }
        this->isNum = false;
        this->exp += "(";
        expressionPanel().Children().Append(makeExpression("("));
        cal();
    }


    void MainPage::closeParenButton_Click(IInspectable const& sender, RoutedEventArgs const& e) {
        if (this->isEnd) {
            clear();
            this->isEnd = false;
        }
        this->isNum = false;
        this->exp += ")";
        expressionPanel().Children().Append(makeExpression(")"));
        cal();
    }


    void MainPage::clearEntryButton_Click(IInspectable const& sender, RoutedEventArgs const& e) {
        clear();
    }


    void MainPage::clearButton_Click(IInspectable const& sender, RoutedEventArgs const& e) {
        clear();
    }


    void MainPage::logicalAndButton_Click(IInspectable const& sender, RoutedEventArgs const& e) {
        if (this->isEnd) {
            clear();
            this->isEnd = false;
        }
        this->isNum = false;
        this->exp += "&";
        expressionPanel().Children().Append(makeExpression("&&"));
        cal();
    }


    void MainPage::logicalOrButton_Click(IInspectable const& sender, RoutedEventArgs const& e) {
        if (this->isEnd) {
            clear();
            this->isEnd = false;
        }
        this->isNum = false;
        this->exp += "|";
        expressionPanel().Children().Append(makeExpression("||"));
        cal();
    }


    void MainPage::logicalNotButton_Click(IInspectable const& sender, RoutedEventArgs const& e) {
        if (this->isEnd) {
            clear();
            this->isEnd = false;
        }
        this->isNum = false;
        this->exp += "!";
        expressionPanel().Children().Append(makeExpression("!"));
        cal();
    }


    void MainPage::divideButton_Click(IInspectable const& sender, RoutedEventArgs const& e) {
        if (this->isEnd) {
            clear();
            this->isEnd = false;
        }
        this->isNum = false;
        this->exp += "/";
        expressionPanel().Children().Append(makeExpression("÷"));
        cal();
    }


    void MainPage::numButton_Click(IInspectable const& sender, RoutedEventArgs const& e) {
        if (this->isEnd) {
            clear();
            this->isEnd = false;
        }
        auto temp = to_string(unbox_value<hstring>(sender.as<Button>().Content()));
        this->exp += temp;
        expressionPanel().Children().Append(makeExpression(temp, this->isNum ? 0 : 2));
        this->isNum = true;
        cal();
    }


    void MainPage::multiplyButton_Click(IInspectable const& sender, RoutedEventArgs const& e) {
        if (this->isEnd) {
            clear();
            this->isEnd = false;
        }
        this->isNum = false;
        this->exp += "*";
        expressionPanel().Children().Append(makeExpression("×"));
        cal();
    }


    void MainPage::minusButton_Click(IInspectable const& sender, RoutedEventArgs const& e) {
        if (this->isEnd) {
            clear();
            this->isEnd = false;
        }
        this->isNum = false;
        this->exp += "-";
        expressionPanel().Children().Append(makeExpression("-"));
        cal();
    }


    void MainPage::plusButton_Click(IInspectable const& sender, RoutedEventArgs const& e) {
        if (this->isEnd) {
            clear();
            this->isEnd = false;
        }
        this->isNum = false;
        this->exp += "+";
        expressionPanel().Children().Append(makeExpression("+"));
        cal();
    }


    void MainPage::negateButton_Click(IInspectable const& sender, RoutedEventArgs const& e) {
        if (this->isEnd) {
            clear();
            this->isEnd = false;
        }
        if (!this->exp.empty() && isdigit(this->exp.back())) {
            auto pos = this->exp.size() - 1;
            while (pos >= 0 && isdigit(this->exp[pos])) --pos;
            ++pos;
            this->exp.insert(pos, "-");
            expressionPanel().Children().InsertAt(pos, makeExpression("-"));
            cal();
        }
    }


    void MainPage::backSpaceButton_Click(IInspectable const& sender, RoutedEventArgs const& e) {
        if (this->isEnd) {
            clear();
            this->isEnd = false;
        }
        if (!this->exp.empty())
            this->exp.pop_back();
        if (expressionPanel().Children().Size() != 0)
            expressionPanel().Children().RemoveAtEnd();
        if (!this->exp.empty())
            this->isNum = isdigit(this->exp.back());
        cal();
    }


    void MainPage::equalButton_Click(IInspectable const& sender, RoutedEventArgs const& e) {
        if (this->isEnd)
            return;
        expressionPanel().Children().Append(makeExpression("="));
        cal();
        this->isEnd = true;
    }


    void MainPage::resultsBlock_SizeChanged(IInspectable const& sender, SizeChangedEventArgs const& e) {
        if (this->isAdjusted)
            return;
        this->isAdjusted = true;
        auto textWidth = sender.as<TextBlock>().ActualWidth();
        auto fontSize = sender.as<TextBlock>().FontSize();
        auto containerWidth = resultsContainer().ActualWidth();
        auto scal = containerWidth / textWidth;
        fontSize = min(46, scal * fontSize);
        sender.as<TextBlock>().FontSize(fontSize);
    }

}
