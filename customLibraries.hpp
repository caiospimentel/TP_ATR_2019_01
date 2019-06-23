#ifndef CUSTOMLIBRARIES_H_
#define CUSTOMLIBRARIES_H_

using namespace std;


/** Instance of a PID controller.
 *
 * @note This structure is only public to be able to do static allocation of it.
 * Do not access its fields directly.
 */
typedef struct {
    float kp;
    float ki;
    float kd;
    float integrator;
    float previous_error;
    float integrator_limit;
    float frequency;
} pid_ctrl_t;

/** Initializes a PID controller. */
void pid_init(pid_ctrl_t *pid);

/** Sets the gains of the given PID. */
void pid_set_gains(pid_ctrl_t *pid, float kp, float ki, float kd);

/** Returns the proportional gains of the controller. */
void pid_get_gains(const pid_ctrl_t *pid, float *kp, float *ki, float *kd);

/** Returns the limit of the PID integrator. */
float pid_get_integral_limit(const pid_ctrl_t *pid);

/** Returns the value of the PID integrator. */
float pid_get_integral(const pid_ctrl_t *pid);

/** Process one step if the PID algorithm. */
float pid_process(pid_ctrl_t *pid, float error);

/** Sets a maximum value for the PID integrator. */
void pid_set_integral_limit(pid_ctrl_t *pid, float max);

/** Resets the PID integrator to zero. */
void pid_reset_integral(pid_ctrl_t *pid);

/** Sets the PID frequency for gain compensation. */
void pid_set_frequency(pid_ctrl_t *pid, float frequency);

/** Gets the PID frequency for gain compensation. */
float pid_get_frequency(const pid_ctrl_t *pid);


// Declaraçoes da parte de temporização
class Timer{
    public:
    void start()
    {
        m_StartTime = std::chrono::system_clock::now();
        m_bRunning = true;
    }
    
    void stop()
    {
        m_EndTime = std::chrono::system_clock::now();
        m_bRunning = false;
    }
    
    double elapsedMilliseconds()
    {
        std::chrono::time_point<std::chrono::system_clock> endTime;
        
        if(m_bRunning)
        {
            endTime = std::chrono::system_clock::now();
        }
        else
        {
            endTime = m_EndTime;
        }
        
        return std::chrono::duration_cast<std::chrono::milliseconds>(endTime - m_StartTime).count();
    }
    
    double elapsedSeconds()
    {
        return elapsedMilliseconds() / 1000.0;
    }

   
    private:
    std::chrono::time_point<std::chrono::system_clock> m_StartTime;
    std::chrono::time_point<std::chrono::system_clock> m_EndTime;
    bool                                               m_bRunning = false;
};

// Declarações do método de integração

float dydx(float qin, float h);

// Finds value of y for a given x using step size h 
// and initial value y0 at x0. 
float rungeKutta(float x0, float y0, float x, float h);

#endif

