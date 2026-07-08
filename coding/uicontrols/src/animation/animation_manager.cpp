// Copyright 2026 uicontrols Project Authors. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "animation_manager.h"

#include <QPropertyAnimation>
#include <QVariantAnimation>

// ---------------------------------------------------------------------------
// AnimHandle
// ---------------------------------------------------------------------------

AnimHandle::AnimHandle(QVariantAnimation* anim)
    : animation_(anim) {}

bool AnimHandle::IsRunning() const {
  return animation_ &&
         animation_->state() == QAbstractAnimation::Running;
}

bool AnimHandle::IsFinished() const {
  return animation_ &&
         animation_->state() == QAbstractAnimation::Stopped;
}

void AnimHandle::Stop() {
  if (animation_) {
    animation_->stop();
  }
}

void AnimHandle::Pause() {
  if (animation_) {
    animation_->pause();
  }
}

void AnimHandle::Resume() {
  if (animation_) {
    animation_->resume();
  }
}

bool AnimHandle::IsValid() const {
  return !animation_.isNull();
}

// ---------------------------------------------------------------------------
// AnimationManager
// ---------------------------------------------------------------------------

AnimationManager::AnimationManager(QObject* parent)
    : QObject(parent) {}

AnimationManager::~AnimationManager() {
  StopAll();
}

AnimHandle AnimationManager::CreateOpacityAnimation(
    QObject* target,
    const QByteArray& propertyName,
    qreal from,
    qreal to,
    int durationMs,
    QEasingCurve::Type easing) {
  auto* anim = new QPropertyAnimation(target, propertyName, this);
  anim->setStartValue(from);
  anim->setEndValue(to);
  anim->setDuration(durationMs);
  anim->setEasingCurve(QEasingCurve(easing));
  anim->start(QAbstractAnimation::DeleteWhenStopped);

  AnimationEntry entry;
  entry.animation = anim;
  entry.target = target;
  animations_.append(entry);

  connect(target, &QObject::destroyed, this, &AnimationManager::OnTargetDestroyed);

  return AnimHandle(anim);
}

AnimHandle AnimationManager::CreateColorAnimation(
    QObject* target,
    const QByteArray& propertyName,
    const QColor& from,
    const QColor& to,
    int durationMs,
    QEasingCurve::Type easing) {
  auto* anim = new QPropertyAnimation(target, propertyName, this);
  anim->setStartValue(from);
  anim->setEndValue(to);
  anim->setDuration(durationMs);
  anim->setEasingCurve(QEasingCurve(easing));
  anim->start(QAbstractAnimation::DeleteWhenStopped);

  AnimationEntry entry;
  entry.animation = anim;
  entry.target = target;
  animations_.append(entry);

  connect(target, &QObject::destroyed, this, &AnimationManager::OnTargetDestroyed);

  return AnimHandle(anim);
}

AnimHandle AnimationManager::CreateProgressAnimation(
    QObject* target,
    const QByteArray& propertyName,
    int durationMs,
    std::function<void(qreal)> callback) {
  auto* anim = new QVariantAnimation(this);
  anim->setStartValue(0.0);
  anim->setEndValue(360.0);
  anim->setDuration(durationMs);
  anim->setLoopCount(-1);  // infinite loop for spinners

  if (callback) {
    connect(anim, &QVariantAnimation::valueChanged, this,
            [callback](const QVariant& value) {
              callback(value.toReal());
            });
  }

  // If a property name is supplied, animate it via QPropertyAnimation wrapper.
  // Otherwise just use the raw QVariantAnimation with the callback.
  if (!propertyName.isEmpty()) {
    auto* propAnim = new QPropertyAnimation(target, propertyName, this);
    propAnim->setDuration(durationMs);
    propAnim->setStartValue(0.0);
    propAnim->setEndValue(360.0);
    propAnim->setLoopCount(-1);

    if (callback) {
      connect(propAnim, &QVariantAnimation::valueChanged, this,
              [callback](const QVariant& value) {
                callback(value.toReal());
              });
    }

    propAnim->start(QAbstractAnimation::DeleteWhenStopped);

    AnimationEntry entry;
    entry.animation = propAnim;
    entry.target = target;
    animations_.append(entry);

    connect(target, &QObject::destroyed, this,
            &AnimationManager::OnTargetDestroyed);

    return AnimHandle(propAnim);
  }

  // No property target - standalone QVariantAnimation with just callback
  // Use a dedicated helper QObject as proxy so cleanup still works.
  auto* proxy = new QObject(this);
  anim->start(QAbstractAnimation::DeleteWhenStopped);

  AnimationEntry entry;
  entry.animation = anim;
  entry.target = proxy;
  animations_.append(entry);

  return AnimHandle(anim);
}

void AnimationManager::StopAll(QObject* target) {
  for (auto it = animations_.begin(); it != animations_.end();) {
    if (it->target.data() == target) {
      if (it->animation) {
        it->animation->stop();
      }
      it = animations_.erase(it);
    } else {
      ++it;
    }
  }
}

void AnimationManager::StopAll() {
  for (const auto& entry : animations_) {
    if (entry.animation) {
      entry.animation->stop();
    }
  }
  animations_.clear();
}

void AnimationManager::OnTargetDestroyed(QObject* target) {
  StopAll(target);
}
