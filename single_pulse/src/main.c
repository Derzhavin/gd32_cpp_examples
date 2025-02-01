#include "gd32f1x0.h"
#include <stdio.h>


void gpio_config(void);
void timer_config(void);

void gpio_config(void)
{
    rcu_periph_clock_enable(RCU_GPIOA);

    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_6);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_6);

    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_7);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_7);
    
    gpio_af_set(GPIOA, GPIO_AF_1, GPIO_PIN_6);
    gpio_af_set(GPIOA, GPIO_AF_1, GPIO_PIN_7);
}


void timer_config(void)
{
    timer_oc_parameter_struct timer_ocinitpara;
    timer_parameter_struct timer_initpara;
    timer_ic_parameter_struct timer_icinitpara;

    rcu_periph_clock_enable(RCU_TIMER2);

    timer_deinit(TIMER2);

    timer_initpara.prescaler         = 3;
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection  = TIMER_COUNTER_UP;
    timer_initpara.period            = 65535;
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
    timer_initpara.repetitioncounter = 0;
    timer_init(TIMER2, &timer_initpara);

    timer_auto_reload_shadow_disable(TIMER2);

    timer_ocinitpara.ocpolarity  = TIMER_OC_POLARITY_HIGH;
    timer_ocinitpara.outputstate = TIMER_CCX_ENABLE;
    timer_ocinitpara.ocidlestate = TIMER_OC_IDLE_STATE_LOW;
    timer_channel_output_config(TIMER2, TIMER_CH_1, &timer_ocinitpara);

    timer_channel_output_pulse_value_config(TIMER2, TIMER_CH_1, 11535);
    timer_channel_output_mode_config(TIMER2, TIMER_CH_1, TIMER_OC_MODE_PWM1);
    timer_channel_output_shadow_config(TIMER2, TIMER_CH_1, TIMER_OC_SHADOW_DISABLE);

    timer_icinitpara.icpolarity  = TIMER_IC_POLARITY_FALLING;
    timer_icinitpara.icselection = TIMER_IC_SELECTION_DIRECTTI;
    timer_icinitpara.icprescaler = TIMER_IC_PSC_DIV1;
    timer_icinitpara.icfilter = 0x00;
    timer_input_capture_config(TIMER2, TIMER_CH_0, &timer_icinitpara);

    timer_single_pulse_mode_config(TIMER2, TIMER_SP_MODE_SINGLE);

    timer_input_trigger_source_select(TIMER2, TIMER_SMCFG_TRGSEL_CI0FE0);
    timer_slave_mode_select(TIMER2, TIMER_SLAVE_MODE_EVENT);
}

/*!
    \brief      main function
    \param[in]  none
    \param[out] none
    \retval     none
*/
int main(void)
{
    gpio_config(); 
    timer_config();

    while (1);
}