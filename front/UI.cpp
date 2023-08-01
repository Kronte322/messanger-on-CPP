#include "./UI.hpp"

#include <iostream>

UI::UI()
    : app_(Gtk::Application::create("Messenger")),
      log_in_window_(*this),
      sign_up_window_(*this) {
  app_->signal_activate().connect([this]() { Start(); });
}

int UI::RunGUI() { return app_->run(); }

LogInWindow& UI::SetLogInWindow() { return log_in_window_; }

SignUpWindow& UI::SetSignUpWindow() { return sign_up_window_; }

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

void LogInWindow::OnLogInButtonClicked() {}

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

void SignUpWindow::OnBackButtonClicked() {
  CloseWindow();
  ui_.SetLogInWindow().OpenWindow();
}

void SignUpWindow::OnSignUpButtonClicked() {
  auto username =
      builder_->get_widget<Gtk::Entry>("username_text_box")->get_text();
  auto password =
      builder_->get_widget<Gtk::Entry>("password_text_box")->get_text();
  auto repeat_password =
      builder_->get_widget<Gtk::Entry>("repeat_password_text_box")->get_text();
  if ((password != repeat_password) || password.empty() || username.empty()) {
    auto label = builder_->get_widget<Gtk::Label>("error_label");
    if (!label->get_visible()) {
      label->show();
    }
  } else {
  }
}