#pragma once
#include <gtkmm.h>

#include <memory>
#include <mutex>
#include <vector>

#include "../back/ClientController.hpp"
#include "../back/ClientStorage.hpp"
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

class MainWindow : public Window {
 public:
  MainWindow(UI& ui);

  void Init() override;
  void OpenWindow() override;
  void CloseWindow() override;

  void OpenCorrectMessage();
  void OpenErrorMessage();

 private:
  void OnSendButtonClicked();
  void OnProfileButtonClicked();
  void OnWindowDraw();
  void UpdateMessages();

  std::mutex mutex_;
  bool sign_ = false;
  int num_of_frames_ = 0;
};

class UI {
 public:
  UI(ClientController& client_controller, ClientStorage& client_storage);

  int RunGUI();

  LogInWindow& SetLogInWindow();

  SignUpWindow& SetSignUpWindow();

  MainWindow& SetMainWindow();

  ClientController& SetClientController();

  ClientStorage& SetClientStorage();

  Glib::RefPtr<Gtk::Application>& SetApp();

 private:
  void Start();

  LogInWindow log_in_window_;
  SignUpWindow sign_up_window_;
  MainWindow main_window_;
  Glib::RefPtr<Gtk::Application> app_;
  ClientController& client_controller_;
  ClientStorage& client_storage_;
};
