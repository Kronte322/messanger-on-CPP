#pragma once
#include <gtkmm.h>

#include <memory>
#include <vector>
class UI;

class Window {
 public:
  Window(UI& ui);

  virtual void Init() = 0;
  virtual void OpenWindow() = 0;
  virtual void CloseWindow() = 0;
  virtual ~Window() = default;

 protected:
  std::shared_ptr<Gtk::Builder> builder_;
  UI& ui_;
};

class LogInWindow : public Window {
 public:
  LogInWindow(UI& ui);

  void Init() override;
  void OpenWindow() override;
  void CloseWindow() override;

 private:
  void OnLogInButtonClicked();
  void OnSignUpButtonClicked();
};

class SignUpWindow : public Window {
 public:
  SignUpWindow(UI& ui);

  void Init() override;
  void OpenWindow() override;
  void CloseWindow() override;

 private:
  void OnBackButtonClicked();
  void OnSignUpButtonClicked();
};

class UI {
 public:
  UI();

  int RunGUI();

  LogInWindow& SetLogInWindow();

  SignUpWindow& SetSignUpWindow();

  Glib::RefPtr<Gtk::Application>& SetApp();

 private:
  void Start();

  LogInWindow log_in_window_;
  SignUpWindow sign_up_window_;
  Glib::RefPtr<Gtk::Application> app_;
};
