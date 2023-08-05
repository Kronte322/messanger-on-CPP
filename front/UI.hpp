#pragma once
#include <gtkmm.h>

#include <memory>
#include <vector>

#include "../back/ClientController.hpp"
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

  void OpenCorrectMessage();
  void OpenErrorMessage();

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

  void OpenCorrectMessage();
  void OpenErrorMessage();

 private:
  void OnBackButtonClicked();
  void OnSignUpButtonClicked();
};

class UI {
 public:
  UI(ClientController& client_controller);

  int RunGUI();

  LogInWindow& SetLogInWindow();

  SignUpWindow& SetSignUpWindow();

  ClientController& SetClientController();

  Glib::RefPtr<Gtk::Application>& SetApp();

 private:
  void Start();

  LogInWindow log_in_window_;
  SignUpWindow sign_up_window_;
  Glib::RefPtr<Gtk::Application> app_;
  ClientController& client_controller_;
};
