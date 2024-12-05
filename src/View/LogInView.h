#include "StateView.h"
#include "../Model/LogInModel.h"
#include <raylib.h>

class LogInView : public StateView, public std::enable_shared_from_this<LogInView>
{
public:
	LogInView();
	LogInView(std::shared_ptr<LogInModel> model);
	LogInView(const LogInView& logInView);

	void render() override;
	void update(std::shared_ptr<Event> event) override;
	void registerSelf() override;
private:
	std::shared_ptr<LogInModel> model;
};