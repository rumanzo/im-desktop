#pragma once

namespace Ui
{
    class LottiePlayer;

    namespace Smiles
    {
        class AttachedView
        {
            QWidget* View_;
            QWidget* ViewParent_;

        public:

            AttachedView(QWidget* _view, QWidget* _viewParent = nullptr);

            QWidget* getView() const;
            QWidget* getViewParent() const;
        };


        class AddButton : public QWidget
        {
            Q_OBJECT

        Q_SIGNALS :
            void clicked();

        public:
            AddButton(QWidget* _parent);

        protected:
            void paintEvent(QPaintEvent* _e) override;
        };


        //////////////////////////////////////////////////////////////////////////
        // TabButton
        //////////////////////////////////////////////////////////////////////////

        class TabButton : public QPushButton
        {
            Q_OBJECT

        public:
            TabButton(QWidget* _parent, QPixmap _pixmap);

            void AttachView(const AttachedView& _view);
            const AttachedView& GetAttachedView() const;

            void setFixed(const bool _isFixed);
            bool isFixed() const;

            void setSetId(int32_t _id) { setId_ = _id; }
            int getSetId() const noexcept { return setId_; }

            void setPixmap(QPixmap _pixmap);
            void setLottie(const QString& _path);

            void onVisibilityChanged(bool _visible);

            static QSize iconSize();

        protected:
            void paintEvent(QPaintEvent* _e) override;
            void resizeEvent(QResizeEvent* event) override;

        private:
            QRect iconRect() const;

        private:
            AttachedView attachedView_ = nullptr;
            bool fixed_ = false;
            int32_t setId_ = -1;
            QPixmap pixmap_;
            LottiePlayer* lottie_ = nullptr;
        };

        //////////////////////////////////////////////////////////////////////////
        // Toolbar
        //////////////////////////////////////////////////////////////////////////

        class ToolbarScrollArea : public QScrollArea
        {
            Q_OBJECT
        public:
            ToolbarScrollArea(QWidget* _parent) : QScrollArea(_parent) {}
            void setRightMargin(const int _margin)
            {
                setViewportMargins(0, 0, _margin, 0);
            }
        };


        class Toolbar : public QFrame
        {
            Q_OBJECT

        public:
            enum class buttonsAlign
            {
                center = 1,
                left = 2,
                right = 3
            };

        private:

            enum class direction
            {
                left = 0,
                right = 1
            };

            buttonsAlign align_;
            QHBoxLayout* horLayout_;
            std::list<TabButton*> buttons_;
            ToolbarScrollArea* viewArea_;

            AddButton* buttonStore_;

            QPropertyAnimation* AnimScroll_;

            void addButton(TabButton* _button);
            void scrollStep(direction _direction);

        private:
            void touchScrollStateChanged(QScroller::State);
            void buttonStoreClick();

            void updateItemsVisibility();

        protected:
            void paintEvent(QPaintEvent* _e) override;
            void resizeEvent(QResizeEvent * _e) override;
            void wheelEvent(QWheelEvent* _e) override;

        public:
            Toolbar(QWidget* _parent, buttonsAlign _align);
            ~Toolbar();

            void Clear(const bool _delFixed = false);

            TabButton* addButton(QPixmap _icon);
            TabButton* addButton(int32_t _setId);
            TabButton* selectedButton() const;
            TabButton* getButton(int32_t _setId) const;

            void scrollToButton(TabButton* _button);

            const std::list<TabButton*>& GetButtons() const;

            void addButtonStore();

            void selectNext();
            void selectPrevious();

            void selectFirst();
            void selectLast();

            bool isFirstSelected() const;
            bool isLastSelected() const;
        };
    }
}