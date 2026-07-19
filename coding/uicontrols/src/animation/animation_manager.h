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

// animation_manager.h — Centralized animation factory for all components.
//
// Components must not create QVariantAnimation / QPropertyAnimation directly.
// Instead, call Create*Animation() on an AnimationManager instance (typically
// owned by the component). Animations auto-cleanup when the target is destroyed.
//
// Supported types: opacity, color, progress (continuous loop for spinners).

#ifndef ANIMATION_ANIMATION_MANAGER_H_
#define ANIMATION_ANIMATION_MANAGER_H_

#include <QAbstractAnimation>
#include <QColor>
#include <QObject>
#include <QPointer>
#include <QVariantAnimation>

#include <functional>

// Lightweight RAII handle to a running animation. Allows callers to stop,
// pause, or query state without tracking the underlying QVariantAnimation*.
class AnimHandle {
 public:
  AnimHandle() = default;
  explicit AnimHandle(QVariantAnimation* anim);

  bool IsRunning() const;
  bool IsFinished() const;
  void Stop();
  void Pause();
  void Resume();
  bool IsValid() const;

 private:
  QPointer<QVariantAnimation> animation_;
};

class AnimationManager : public QObject {
  Q_OBJECT

 public:
  explicit AnimationManager(QObject* parent = nullptr);
  ~AnimationManager() override;

  AnimHandle CreateOpacityAnimation(QObject* target,
                                    const QByteArray& propertyName,
                                    qreal from,
                                    qreal to,
                                    int durationMs,
                                    QEasingCurve::Type easing =
                                        QEasingCurve::Linear);

  AnimHandle CreateColorAnimation(QObject* target,
                                  const QByteArray& propertyName,
                                  const QColor& from,
                                  const QColor& to,
                                  int durationMs,
                                  QEasingCurve::Type easing =
                                      QEasingCurve::Linear);

  AnimHandle CreateProgressAnimation(
      QObject* target,
      const QByteArray& propertyName,
      int durationMs,
      std::function<void(qreal)> callback = nullptr);

  void StopAll(QObject* target);
  void StopAll();

 private:
  void OnTargetDestroyed(QObject* target);

  struct AnimationEntry {
    QPointer<QVariantAnimation> animation;
    QPointer<QObject> target;
  };
  QList<AnimationEntry> animations_;
};

#endif  // ANIMATION_ANIMATION_MANAGER_H_
