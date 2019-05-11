/**
 * @file    PostProcess.h
 * @author  ggomdyu
 * @since   10/22/2017
 */

#pragma once

class PostProcess
{
public:
    virtual ~PostProcess() = default;

public:
    virtual void BeginScene() = 0;
    virtual void Draw() = 0;
};

class BlurPostProcess :
    public PostProcess
{
public:
    virtual void BeginScene() override {}
    virtual void Draw() override {}
};
