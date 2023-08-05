#include "./UI.hpp"

#include <iostream>
#include <thread>

UI::UI(ClientController& client_controller)
    : app_(Gtk::Application::create("Messenger")),
      log_in_window_(*this),
      sign_up_window_(*this),
      client_controller_(client_controller) {
  app_->signal_activate().connect([this]() { Start(); });
}

int UI::RunGUI() { return app_->run(); }

LogInWindow& UI::SetLogInWindow() { return log_in_window_; }

SignUpWindow& UI::SetSignUpWindow() { return sign_up_window_; }

ClientController& UI::SetClientController() { return client_controller_; }

Glib::RefPtr<Gtk::Application>& UI::SetApp() { return app_; }

void UI::Start() {
  log_in_window_.Init();
  sign_up_window_.Init();

  log_in_window_.OpenWindow();
}

Window::Window(UI& ui) : ui_(ui), builder_(Gtk::Builder::create()) {}

LogInWindow::LogInWindow(UI& ui) : Window(ui) {}

void LogInWindow::Init() {
  builder_->add_from_file("../front/ui_templates/log_in.ui");

  auto log_in_button = builder_->get_widget<Gtk::Button>("log_in_button");
  log_in_button->signal_clicked().connect([this]() { OnLogInButtonClicked(); });

  auto sign_up_button = builder_->get_widget<Gtk::Button>("sign_up_button");
  sign_up_button->signal_clicked().connect(
      [this]() { OnSignUpButtonClicked(); });
}

void LogInWindow::OpenWindow() {
  auto window = builder_->get_widget<Gtk::Window>("window");
  window->show();
  ui_.SetApp()->add_window(*window);
}

void LogInWindow::CloseWindow() {
  auto window = builder_->get_widget<Gtk::Window>("window");
  window->hide();
}

void LogInWindow::OpenCorrectMessage() {
  auto label = builder_->get_widget<Gtk::Label>("correct_label");
  auto error_label = builder_->get_widget<Gtk::Label>("error_label");
  if (!label->get_visible()) {
    label->show();
  }
  if (error_label->get_visible()) {
    error_label->hide();
  }
}

void LogInWindow::OpenErrorMessage() {
  auto label = builder_->get_widget<Gtk::Label>("error_label");
  auto correct_label = builder_->get_widget<Gtk::Label>("correct_label");
  if (!label->get_visible()) {
    label->show();
  }
  if (correct_label->get_visible()) {
    correct_label->hide();
  }
}

void LogInWindow::OnLogInButtonClicked() {
  auto user_name =
      builder_->get_widget<Gtk::Entry>("username_text_box")->get_text();
  auto password =
      builder_->get_widget<Gtk::Entry>("password_text_box")->get_text();
  if (!user_name.empty() && !password.empty()) {
    std::thread([this, &user_name, &password]() {
      auto response =
          ui_.SetClientController().SendLogInMessage(user_name, password);
      if (response == -1) {
        OpenErrorMessage();
      } else {
        OpenCorrectMessage();
      }
    }).detach();
  } else {
    OpenErrorMessage();
  }
}

void LogInWindow::OnSignUpButtonClicked() {
  CloseWindow();
  ui_.SetSignUpWindow().OpenWindow();
}

SignUpWindow::SignUpWindow(UI& ui) : Window(ui) {}

void SignUpWindow::Init() {
  builder_->add_from_file("../front/ui_templates/sign_up.ui");

  auto sign_up_button = builder_->get_widget<Gtk::Button>("sign_up_button");
  sign_up_button->signal_clicked().connect(
      [this]() { OnSignUpButtonClicked(); });

  auto back_button = builder_->get_widget<Gtk::Button>("back_button");
  back_button->signal_clicked().connect([this]() { OnBackButtonClicked(); });
}

void SignUpWindow::OpenWindow() {
  auto window = builder_->get_widget<Gtk::Window>("window");
  window->show();
  ui_.SetApp()->add_window(*window);
}

void SignUpWindow::CloseWindow() {
  auto window = builder_->get_widget<Gtk::Window>("window");
  window->hide();
}

void SignUpWindow::OpenCorrectMessage() {
  auto label = builder_->get_widget<Gtk::Label>("correct_label");
  auto error_label = builder_->get_widget<Gtk::Label>("error_label");
  if (!label->get_visible()) {
    label->show();
  }
  if (error_label->get_visible()) {
    error_label->hide();
  }
}

void SignUpWindow::OpenErrorMessage() {
  auto label = builder_->get_widget<Gtk::Label>("error_label");
  auto correct_label = builder_->get_widget<Gtk::Label>("correct_label");
  if (!label->get_visible()) {
    label->show();
  }
  if (correct_label->get_visible()) {
    correct_label->hide();
  }
}

void SignUpWindow::OnBackButtonClicked() {
  CloseWindow();
  ui_.SetLogInWindow().OpenWindow();
}

void SignUpWindow::OnSignUpButtonClicked() {
  auto user_name =
      builder_->get_widget<Gtk::Entry>("username_text_box")->get_text();
  auto password =
      builder_->get_widget<Gtk::Entry>("password_text_box")->get_text();
  auto repeat_password =
      builder_->get_widget<Gtk::Entry>("repeat_password_text_box")->get_text();
  if ((password != repeat_password) || password.empty() || user_name.empty()) {
    OpenErrorMessage();
  } else {
    std::thread([this, &user_name, &password]() {
      auto response =
          ui_.SetClientController().SendSignUpMessage(user_name, password);
      if (response == -1) {
        OpenErrorMessage();
      } else {
        OpenCorrectMessage();
      }
    }).detach();
  }
}