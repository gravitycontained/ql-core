#pragma once

#define ql_state_interactive(param)                      \
	void call_init_interaction() override                  \
	{                                                      \
		this->interactive_init_interaction(param);           \
	}                                                      \
	void call_init() override                              \
	{                                                      \
		this->interactive_init(param);                       \
	}                                                      \
                                                         \
	void call_update_new() override                        \
	{                                                      \
		this->interactive_update_new(param);                 \
	}                                                      \
                                                         \
	void call_update() override                            \
	{                                                      \
		this->interactive_update(param);                     \
	}                                                      \
                                                         \
	void call_update_injection() override                  \
	{                                                      \
		this->interactive_update_injection(param);           \
	}                                                      \
                                                         \
	void call_provide() override                           \
	{                                                      \
		this->interactive_provide(param);                    \
	}                                                      \
                                                         \
	void call_phase_signal_run() override                  \
	{                                                      \
		this->interactive_update_phase_signal_run(param);    \
	}                                                      \
                                                         \
	void call_phase_signal_detect() override               \
	{                                                      \
		this->interactive_update_phase_signal_detect(param); \
	}                                                      \
                                                         \
	void call_draw() override                              \
	{                                                      \
		this->interactive_draw(param);                       \
	}\
