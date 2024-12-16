#pragma once

#define ql_state_sync(param)                       \
                                                   \
	void init_before() override                      \
	{                                                \
		this->sync_init_before(param);                 \
	}                                                \
                                                   \
	void call_init() override                        \
	{                                                \
		this->sync_init(param);                        \
	}                                                \
                                                   \
	void call_update() override                      \
	{                                                \
		this->sync_update(param);                      \
	}                                                \
                                                   \
	void call_update_injection() override            \
	{                                                \
		this->sync_update_injection(param);            \
	}                                                \
                                                   \
	void call_provide() override                     \
	{                                                \
		this->sync_provide(param);                     \
	}                                                \
                                                   \
	void call_phase_signal_run() override            \
	{                                                \
		this->sync_update_phase_signal_run(param);     \
	}                                                \
                                                   \
	void call_phase_signal_detect() override         \
	{                                                \
		this->sync_update_phase_signal_detect(param);  \
	}                                                \
                                                   \
	void call_draw() override                        \
	{                                                \
		this->sync_draw(param);                        \
	}																								 \
